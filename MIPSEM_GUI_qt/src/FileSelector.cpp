#include "FileSelector.hpp"

FileSelector::FileSelector(QWidget *parent)
    :   QWidget(parent), layout(this),
      buttonRootDirUp(), buttonRootDirSelect(),
      fileSystemModel(), treeView()
{
    
    //buttons
    
    buttonRootDirUp.setText(BUTTONROOTDIRUP_TEXT);
    buttonRootDirUp.setStyleSheet("font-weight:bold");
    connect(&buttonRootDirUp, SIGNAL(clicked()), this, SLOT(slotRootDirUp()));
    layout.addWidget(&buttonRootDirUp, 0, 0, 1, 1);
    
    buttonRootDirSelect.setText(BUTTONROOTDIRSELECT_TEXT);
    buttonRootDirSelect.setStyleSheet("font-weight:bold");
    connect(&buttonRootDirSelect, SIGNAL(clicked()), this, SLOT(slotRootDirSelect()));
    layout.addWidget(&buttonRootDirSelect, 0, 1, 1, 3);
    
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
    
    layout.addWidget(&treeView, 1, 0, 1, 4);
    
}
FileSelector::~FileSelector(){
       
}


void FileSelector::slotRootDirUp(){
    
}

void FileSelector::slotRootDirSelect(){
        
}
