#include "FileEditor.hpp"

#include "MIPSEM_CORE/Parser.hpp"

#include <string>

#include <QApplication>
#include <QMessageBox>
#include <QTextStream>

using std::string;

FileEditor::FileEditor(QString const &dir, QTabWidget *tabbedFileEditor, QWidget *parent)
    :   QPlainTextEdit(parent), dir(dir), tabbedFileEditor(tabbedFileEditor)
{
    init_pointers();
    init();
}
void FileEditor::init(){
    connect(this, SIGNAL(signalRefreshSyntaxHighlighter()), 
            this, SLOT(refreshSyntaxHighlighter()));
    connect(shortcutSave, SIGNAL(activated()), 
            this, SLOT(slotSaveFile()));
    connect(this, SIGNAL(cursorPositionChanged()), 
            this, SLOT(highlightCurrentLine()));
    name = QString(Parser::filePathToFileName(dir.toStdString()).c_str());
    readFile(dir);
    modifiedSinceLastSave = false;
    //setTitle(name);
    connect(this, SIGNAL(textChanged()),
            this, SLOT(modified()));
}
void FileEditor::init_pointers(){
    highlighter = new MIPS32SyntaxHighlighter(this);
    shortcutSave = new QShortcut(QKeySequence("Ctrl+s"), this);
}

FileEditor::~FileEditor(){ 
    deinit();
}
void FileEditor::deinit(){
    delete highlighter;
    delete shortcutSave;  
}


void FileEditor::selectLine(unsigned int lineNum){
    QTextCursor cursor(this->textCursor());
    QTextBlock textBlock = this->document()->findBlockByNumber(lineNum);
    cursor.setPosition(textBlock.position());
    //cursor.setPosition(QTextCursor::atBlockStart());
    this->setTextCursor(cursor);
}


bool FileEditor::saveFile(){
    if(!modifiedSinceLastSave){
        //do nothing
    }else{
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
        QApplication::restoreOverrideCursor();
    }
    modifiedSinceLastSave = false;
    setTitle(name);
}

bool FileEditor::requestSave(){
    if(!modifiedSinceLastSave){return true;}
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
    QApplication::restoreOverrideCursor();
}


void FileEditor::setTitle(QString string){
    setDocumentTitle(string);
    if(tabbedFileEditor != NULL){
        int index = tabbedFileEditor->indexOf(this);
        tabbedFileEditor->setTabText(index, string);
    }
}

void FileEditor::modified(){
    if(!modifiedSinceLastSave){
        setTitle("*" + name);
    }
    modifiedSinceLastSave = true;   
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

void FileEditor::highlightCurrentLine(){
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;
        selection.format.setBackground(highlighter->backgroundHighlightColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
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





