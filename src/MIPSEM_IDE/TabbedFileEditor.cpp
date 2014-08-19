#include "TabbedFileEditor.hpp"

#include "MIPSEM_CORE/Parser.hpp"

#include <QMessageBox>
#include <string>

using std::string;

TabbedFileEditor::TabbedFileEditor(QWidget *parent)
    :QTabWidget(parent)
{
    this->setMovable(true);
    this->setTabsClosable(true);
    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(slotRequestCloseTab(int)));
}
TabbedFileEditor::~TabbedFileEditor(){
    for(int i=0; i<editors.size(); i++){
        delete editors[i];   
    }   
}

void TabbedFileEditor::editFile(QString const &dir){
    if(hasFileOpen(dir)){
        focusOnFile(dir);
        //return true;
        return;
    }
    QFile file(dir);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot open file %1:\n%2.")
                             .arg(dir)
                             .arg(file.errorString()));
        //return false;
        return;
    }
    file.close();
    
    QString fileName = QString(Parser::filePathToFileName(dir.toStdString()).c_str());    
    FileEditor *editor = new FileEditor(dir, this);
    editors.push_back(editor);
    int index = this->addTab(editor, fileName);
    this->setCurrentIndex(index);
    
}

bool TabbedFileEditor::hasFileOpen(QString const &dir){
    return getDirectoryFileEditor(dir) != NULL;
}

void TabbedFileEditor::focusOnFile(QString const &dir){
    for(int i=0; i<this->count(); i++){
        FileEditor* editor = (FileEditor*)this->widget(i);
        QString tabFileName = editor->dir;
        if(tabFileName == dir){
            this->setCurrentIndex(i);
        }
    } 
}

FileEditor* TabbedFileEditor::getDirectoryFileEditor(QString const &dir){
    for(int i=0; i<this->count(); i++){
        FileEditor* editor = (FileEditor*)this->widget(i);
        QString tabFileName = editor->dir;
        if(tabFileName == dir){return editor;}
    }
    return NULL;
}


bool TabbedFileEditor::requestCloseTab(int index){
    FileEditor* editor = (FileEditor*)this->widget(index);
    if(!editor->requestSave()){
        return false; 
    } 
    this->removeTab(index);
    for(int i=0; i<editors.size(); i++){
       if(editors[i] == editor){
            editors.erase(editors.begin() + i); 
            break;
       }
    }
    delete editor;
}

bool TabbedFileEditor::requestCloseAllTabs(){
    for(int i=0; i<this->count();){//no i++ because count is lowering each time one's closed
        if(!requestCloseTab(i)){return false;}   
    }   
}

bool TabbedFileEditor::saveAllTabs(){
    for(int i=0; i<this->count(); i++){
        FileEditor* editor = (FileEditor*)this->widget(i);
        if(!editor->saveFile()){
            return false;   
        }
    }   
    return true;
}

void TabbedFileEditor::selectFileLine(ProgramLine const &programLine){
    editFile(QString(programLine.fileName.c_str()));
    FileEditor* editor = (FileEditor*)(this->currentWidget());
    editor->selectLine(programLine.lineNumber);
}

void TabbedFileEditor::slotRequestCloseTab(int index){
    requestCloseTab(index);
}






























