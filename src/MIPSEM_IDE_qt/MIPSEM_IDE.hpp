#ifndef FILEBROWSER_HPP
#define FILEBROWSER_HPP

#include "AssemblerExceptionView.hpp"
#include "FileSelector.hpp"
#include "TabbedFileEditor.hpp"


class MIPSEM_IDE : public QWidget{
    Q_OBJECT
    
    public:
        MIPSEM_IDE(QWidget *parent = NULL);
        ~MIPSEM_IDE();
        
        
        QGridLayout *layout;
        
        QSplitter *middle;
           TabbedFileEditor *tabbedFileEditor;
           FileSelector *fileSelector;
        QSplitter *bottom;
           AssemblerExceptionView *assemblerExceptionView;
    
    
};





#endif // FILEBROWSER_HPP
