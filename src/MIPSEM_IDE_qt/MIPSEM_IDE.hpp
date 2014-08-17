#ifndef FILEBROWSER_HPP
#define FILEBROWSER_HPP

#include "AssemblerExceptionView.hpp"
#include "FileSelector.hpp"
#include "TabbedFileEditor.hpp"

class MIPSEM_IDE : public QSplitter{
    Q_OBJECT
    
    public:
        MIPSEM_IDE(QWidget *parent = NULL);
        
        QSplitter fileEditSection;
        
        TabbedFileEditor tabbedFileEditor;
        FileSelector fileSelector;
        AssemblerExceptionView assemblerExceptionView;
    
    
};





#endif // FILEBROWSER_HPP
