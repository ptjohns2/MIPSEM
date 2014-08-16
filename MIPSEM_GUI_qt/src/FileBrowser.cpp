#include "FileBrowser.hpp"



FileBrowser::FileBrowser(QWidget *parent)
    :   QSplitter(parent)
      //tabbedFileEditor(), fileSelector()
{
    
    this->addWidget(&fileSelector);
    this->addWidget(&tabbedFileEditor);
    
    connect(&fileSelector, SIGNAL(fileSelected(QString const &)), &tabbedFileEditor, SLOT(editFile(QString const &)));
    
}
