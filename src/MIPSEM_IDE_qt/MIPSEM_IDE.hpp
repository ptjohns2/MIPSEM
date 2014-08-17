#ifndef FILEBROWSER_HPP
#define FILEBROWSER_HPP

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
    
    
};





#endif // FILEBROWSER_HPP
