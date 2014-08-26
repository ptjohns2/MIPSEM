#ifndef TOOLBAR_HPP
#define TOOLBAR_HPP

#include <QMenu>
#include <QToolBar>

class Toolbar : public QToolBar{
    Q_OBJECT   
    
    public:
        Toolbar();
        void init();
        void init_pointers();
        ~Toolbar();
        void deinit();
        
        QMenu *fileMenu;
            QAction *newFile, *openFile, *closeFile, *saveFile, *saveAllFiles, *exit;
        QMenu *editMenu;
            QAction *undo, *redo, *cut, *copy, *paste, *selectAll, *find, *replace;
        QMenu *viewMenu;
            QAction *zoomIn, *zoomOut, *editSyntaxHighlighter;
        QMenu *emulateMenu;
            QAction *build, *run, *buildAndRun;
        QMenu *helpMenu;
            QAction *MIPSEHelp, *QtHelp;
        
        
        
        
        

};

#endif // TOOLBAR_HPP
