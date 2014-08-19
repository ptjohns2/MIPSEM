#ifndef FILEBROWSER_HPP
#define FILEBROWSER_HPP

#include "MIPSEM_CORE/Core.hpp"

#include "AssemblerExceptionView.hpp"
#include "FileSelector.hpp"
#include "TabbedFileEditor.hpp"

#include <QToolBar>


class MIPSEM_IDE : public QWidget{
    Q_OBJECT
    
    public:
        MIPSEM_IDE(QWidget *parent = NULL);
        void init();
        void init_pointers();
        ~MIPSEM_IDE();
        void deinit();
        
        
        QGridLayout *layout;
        
        QToolBar *toolbar;
        QSplitter *middle;
           TabbedFileEditor *tabbedFileEditor;
           FileSelector *fileSelector;
        QSplitter *bottom;
           AssemblerExceptionView *assemblerExceptionView;
          
           Core core;
           
           
    public slots:
        void assembleOpenFile();
           
};





#endif // FILEBROWSER_HPP
