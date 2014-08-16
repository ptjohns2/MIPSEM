#include "FileSelector.hpp"

#include <QFileDialog>

FileSelector::FileSelector(QWidget *parent)
    :   QWidget(parent), layout(this),
      buttonRootDirSelect(), 
      buttonNew(), buttonNewMenu(),
      fileSystemModel(), treeView()
{
    
    //buttons
    buttonRootDirSelect.setText(BUTTONROOTDIRSELECT_TEXT);
    buttonRootDirSelect.setStyleSheet("font-weight:bold");
    connect(&buttonRootDirSelect, SIGNAL(clicked()), this, SLOT(slotRootDirSelect()));
    layout.addWidget(&buttonRootDirSelect);
       
    
    
    
    rootDir = "";
    fileSystemModel.setRootPath(rootDir);
    
    treeView.setModel(&fileSystemModel);
    //remove the 3 columns after "Name" in file viewer
    for(int i=1; i<=3; i++){
       treeView.hideColumn(i);
    }
    
    // Demonstrating look and feel features
    treeView.setAnimated(false);
    treeView.setIndentation(10);
    treeView.setSortingEnabled(true);
    
    layout.addWidget(&treeView);
    
}
FileSelector::~FileSelector(){
       
}


void FileSelector::slotRootDirSelect(){
    rootDir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    fileSystemModel.setRootPath(rootDir);
    treeView.setRootIndex(fileSystemModel.index(rootDir));
}

\










