#ifndef FILEBROWSER_HPP
#define FILEBROWSER_HPP

#include "AssemblerExceptionView.hpp"
#include "FileSelector.hpp"
#include "TabbedFileEditor.hpp"

class FileBrowser : public QSplitter{
    Q_OBJECT
    
    public:
        FileBrowser(QWidget *parent = NULL);
        
        QSplitter fileEditSection;
        
        TabbedFileEditor tabbedFileEditor;
        FileSelector fileSelector;
        AssemblerExceptionView assemblerExceptionView;
    
    
};





#endif // FILEBROWSER_HPP
