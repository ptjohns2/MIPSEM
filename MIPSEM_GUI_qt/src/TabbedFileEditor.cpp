#include "TabbedFileEditor.hpp"

#include <QMessageBox>


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
    
    //get filename without earlier directory names
    QString tmpDir = dir;
    int i = tmpDir.length();
    for(; i>0; i--){
        if(tmpDir[i] == '\\' || tmpDir[i] == '/'){
            i++;
            break;   
        }   
    }
    QString fileName = tmpDir.mid(i);
    
    FileEditor *editor = new FileEditor(dir);
    editors.push_back(editor);
    this->addTab(editor, fileName);
    
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
       }
    }
    delete editor;
}

bool TabbedFileEditor::requestCloseAllTabs(){
    for(int i=0; i<this->count(); i++){
        if(!requestCloseTab(i)){return false;}   
    }   
}



void TabbedFileEditor::slotRequestCloseTab(int index){
    requestCloseTab(index);
}






























