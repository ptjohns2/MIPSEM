#include "Toolbar.hpp"


Toolbar::Toolbar(QWidget *parent)
    :   QMenuBar(parent)
{
    init_pointers();
    init();
    
}
void Toolbar::init(){ 
    this->addMenu(fileMenu);
    this->addMenu(editMenu);
    this->addMenu(viewMenu);
    this->addMenu(emulateMenu);
    this->addMenu(helpMenu);
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
