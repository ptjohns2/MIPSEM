#include "FileBrowser.hpp"



FileBrowser::FileBrowser(QWidget *parent)
    :   QSplitter(parent)
      //tabbedFileEditor(), fileSelector()
{
    
    this->addWidget(&fileSelector);
    this->addWidget(&tabbedFileEditor);
    this->setStretchFactor(1, 1);
    this->setStretchFactor(0, 0);
    connect(&fileSelector, SIGNAL(fileSelected(QString const &)), &tabbedFileEditor, SLOT(editFile(QString const &)));
    
}
