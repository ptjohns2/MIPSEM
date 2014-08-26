#include "Toolbar.hpp"


Toolbar::Toolbar(QWidget *parent)
    :   QMenuBar(parent)
{
    init_pointers();
    init();
    
}
void Toolbar::init(){ 
        fileMenu->addAction(newFile);
        fileMenu->addAction(openFile);
        //fileMenu->addAction(closeFile);
        fileMenu->addAction(saveFile);
        fileMenu->addAction(saveAllFiles);
        fileMenu->addAction(exit); 
    this->addMenu(fileMenu);
        
        editMenu->addAction(undo);
        editMenu->addAction(redo);
        editMenu->addAction(cut);
        editMenu->addAction(copy);
        editMenu->addAction(paste);
        editMenu->addAction(selectAll);
        editMenu->addAction(find);
        editMenu->addAction(replace);
    this->addMenu(editMenu);
        
        viewMenu->addAction(zoomIn);
        viewMenu->addAction(zoomOut);
        viewMenu->addAction(editSyntaxHighlighting);
    this->addMenu(viewMenu);
        
        emulateMenu->addAction(build);
        emulateMenu->addAction(run);
        emulateMenu->addAction(buildAndRun);
    this->addMenu(emulateMenu);
        
        helpMenu->addAction(MIPSEMHelp);
        helpMenu->addAction(QtHelp);
    this->addMenu(helpMenu);
        
}
void Toolbar::init_pointers(){
    fileMenu = new QMenu("File");
        newFile = new QAction(QIcon(":/images/new.png"), "New...", this);
        openFile = new QAction(QIcon(":/images/open.png"), "Open...", this);
        //closeFile = new QAction(
        saveFile = new QAction(QIcon(":/images/save.png"), "Save", this);
        saveAllFiles = new QAction(QIcon(":/images/saveall.png"), "Save all", this);
        exit = new QAction(QIcon(":/images/exit.png"), "Exit", this);
    editMenu = new QMenu("Edit");
        undo = new QAction(QIcon(":/images/undo.png"), "Undo", this);
        redo = new QAction(QIcon(":/images/redo.png"), "Redo", this);
        cut = new QAction(QIcon(":/images/cut.png"), "Cut", this);
        copy = new QAction(QIcon(":/images/copy.png"), "Copy", this);
        paste = new QAction(QIcon(":/images/paste.png"), "Paste", this);
        selectAll = new QAction(QIcon(":/images/selectall.png"), "Select all", this);
        find = new QAction(QIcon(":/images.find"), "Find...", this);
        replace = new QAction(QIcon(":/images/replace"), "Replace...", this);
    viewMenu = new QMenu("View");
        zoomIn = new QAction(QIcon(":/images"), "Zoom in", this);
        zoomOut = new QAction(QIcon(":/images/zoom.png"), "Zoom out", this);
        editSyntaxHighlighting = new QAction("Edit syntax highlighting...", this);
    emulateMenu = new QMenu("Emulate");
        build = new QAction("Build", this);
        run = new QAction("Run", this);
        buildAndRun = new QAction("Build and run", this);
    helpMenu = new QMenu("Help");
        MIPSEMHelp = new QAction("MIPSEM help", this);
        QtHelp = new QAction("Qt help", this);
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
            zoomIn, zoomOut, editSyntaxHighlighting;
        emulateMenu,
            build, run, buildAndRun,
        helpMenu,
            MIPSEMHelp, QtHelp
    ;
}
























