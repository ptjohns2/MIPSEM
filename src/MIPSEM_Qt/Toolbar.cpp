#include "Toolbar.hpp"


Toolbar::Toolbar(QWidget *parent)
    :   QToolBar(parent)
{
    init_pointers();
    init();
    
}
void Toolbar::init(){
        
    this->addWidget(fileMenu);
    
    this->addWidget(editMenu);
    
    this->addWidget(viewMenu);
    
    this->addWidget(emulateMenu);
    
    this->addWidget(viewMenu);

}
void Toolbar::init_pointers(){
    fileMenu = new QMenu("File");
    
    editMenu = new QMenu("Edit");
    
    viewMenu = new QMenu("View");
    
    emulateMenu = new QMenu("Emulate");
    
    helpMenu = new QMenu("Help");
}

Toolbar::~Toolbar(){
    //deinit();
}
void Toolbar::deinit(){
    delete 
        fileMenu,  
            newFile, openFile, closeFile, saveFile, saveAllFiles, exit,
        editMenu,
            undo, redo, cut, copy, paste, selectAll, find, replace,
        viewMenu,
            zoomIn, zoomOut, editSyntaxHighlighter;
        emulateMenu,
            build, run, buildAndRun,
        helpMenu,
            MIPSEMHelp, QtHelp
    ;
}
