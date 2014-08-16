#ifndef FILEBROWSER_HPP
#define FILEBROWSER_HPP

#include "FileSelector.hpp"
#include "TabbedFileEditor.hpp"

class FileBrowser : public QSplitter{
    Q_OBJECT
    
    public:
        FileBrowser(QWidget *parent = NULL);
        
        TabbedFileEditor tabbedFileEditor;
        FileSelector fileSelector;
    
    
};





#endif // FILEBROWSER_HPP
