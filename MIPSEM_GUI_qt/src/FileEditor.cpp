#include "FileEditor.hpp"

#include <QApplication>
#include <QMessageBox>
#include <QTextStream>

FileEditor::FileEditor(QString const &dir, QWidget *parent)
    :   QPlainTextEdit(parent), dir(dir)
{
    highlighter = new MIPS32SyntaxHighlighter(this);
    connect(this, SIGNAL(signalRefreshSyntaxHighlighter()), this, SLOT(refreshSyntaxHighlighter()));
    
    shortcutSave = new QShortcut(QKeySequence("Ctrl+s"), this);
    connect(shortcutSave, SIGNAL(activated()), this, SLOT(slotSaveFile()));
    readFile(dir);
}

FileEditor::~FileEditor(){
    delete highlighter;
    delete shortcutSave;   
}


void FileEditor::selectLine(unsigned int lineNum){
    QTextCursor cursor(this->textCursor());
    QTextBlock textBlock = this->document()->findBlockByLineNumber(lineNum);
    cursor.setPosition(textBlock.position());
    //cursor.setPosition(QTextCursor::atBlockStart());
    this->setTextCursor(cursor);
}


bool FileEditor::saveFile(){
    if(!modifiedSinceLastSave()){return true;}
    
    //FIX MAKE MINE
    //TODO:
    QFile file(dir);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(dir)
                             .arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    QString plainText = this->toPlainText();
    out << plainText;
    file.flush();
    file.close();
    lastSavedContents = plainText;
    QApplication::restoreOverrideCursor();
    
}

bool FileEditor::requestSave(){
    if(!modifiedSinceLastSave()){return true;}
    QMessageBox msg;
    msg.setText("This document has been modified.");
    msg.setInformativeText("Do you want to save your changes?");
    msg.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msg.setDefaultButton(QMessageBox::Save);
    int answer = msg.exec();
    switch(answer){
        case QMessageBox::Save:
            return saveFile();
            break;
        case QMessageBox::Discard:
            return true;
            break;
        case QMessageBox::Cancel:
            return false;
            break;
        default:
            return false;
            break;
    }
}

bool FileEditor::readFile(QString const &dir){
    //FIX MAKE MINE
    //TODO:
    QFile file(dir);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(dir)
                             .arg(file.errorString()));
        return false;
    }

    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    QString plainText = in.readAll();
    this->setPlainText(plainText);
    file.flush();
    file.close();
    lastSavedContents = plainText;
    QApplication::restoreOverrideCursor();
}


bool FileEditor::modifiedSinceLastSave(){
    return this->toPlainText() != lastSavedContents;   
}


void FileEditor::refreshSyntaxHighlighter(){
    highlighter->refreshEditor();
}

void FileEditor::slotSaveFile(){
    saveFile();   
}

void FileEditor::paintEvent(QPaintEvent *event){
    emit signalRefreshSyntaxHighlighter();
    QPlainTextEdit::paintEvent(event);
}

void FileEditor::wheelEvent(QWheelEvent *event){
    if(QApplication::keyboardModifiers() == Qt::KeyboardModifier::ControlModifier){
           if(event->delta() < 0){
               MIPS32SyntaxHighlighter::decreaseFontSize();   
           }else if(event->delta() == 0){
               //do nothing, why did this event happen lol?
           }else{
               MIPS32SyntaxHighlighter::increaseFontSize();   
           }
           this->update();
    }else{
        QPlainTextEdit::wheelEvent(event);   
    }
}





