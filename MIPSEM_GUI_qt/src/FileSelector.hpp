#ifndef FILESELECTOR_HPP
#define FILESELECTOR_HPP

#include <QGridLayout>
#include <QFileSystemModel>
#include <QPushButton>
#include <QSplitter>
#include <QTreeView>

class FileSelector : public QWidget{
    Q_OBJECT
    
    public:
        FileSelector(QWidget *parent = NULL);
        ~FileSelector();
        
        QGridLayout layout;
        
        #define BUTTONROOTDIRUP_TEXT    ("^")
        QPushButton buttonRootDirUp;
        #define BUTTONROOTDIRSELECT_TEXT    ("?")
        QPushButton buttonRootDirSelect;
        
        QFileSystemModel fileSystemModel;
        QTreeView treeView;
        QString rootDir;

    signals:
        
        
    public slots:
        void slotRootDirUp();
        void slotRootDirSelect();
    
};














#endif // FILESELECTOR_HPP
