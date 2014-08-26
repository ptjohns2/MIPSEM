#ifndef TOOLBAR_HPP
#define TOOLBAR_HPP

#include <QMenu>
#include <QMenuBar>
#include <QToolButton>

class Toolbar : public QMenuBar{
    Q_OBJECT   
    
    public:
        Toolbar(QWidget *parent = NULL);
        void init();
        void init_pointers();
        ~Toolbar();
        void deinit();
    
        QMenu *fileMenu;
            QAction *newFile, *openFile, *closeFile, *saveFile, *saveAllFiles, *exit;
        QMenu *editMenu;
            QAction *undo, *redo, *cut, *copy, *paste, *selectAll, *find, *replace;
        QMenu *viewMenu;
            QAction *zoomIn, *zoomOut, *editSyntaxHighlighting;    
        QMenu *emulateMenu;
            QAction *build, *run, *buildAndRun;
        QMenu *helpMenu;
            QAction *MIPSEMHelp, *QtHelp;
    
        
        
        
        

};

#endif // TOOLBAR_HPP
