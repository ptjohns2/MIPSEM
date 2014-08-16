#ifndef FILESELECTOR_HPP
#define FILESELECTOR_HPP

#include <QGridLayout>
#include <QFileSystemModel>
#include <QToolButton>
#include <QMenu>
#include <QPushButton>
#include <QSplitter>
#include <QTreeView>

class FileSelector : public QWidget{
    Q_OBJECT
    
    public:
        FileSelector(QWidget *parent = NULL);
        ~FileSelector();
        
        QGridLayout layout;
        
        #define BUTTONROOTDIRSELECT_TEXT    ("root directory")
        QPushButton buttonRootDirSelect;
        QToolButton buttonNew;
        QMenu buttonNewMenu;
        
        QFileSystemModel fileSystemModel;
        QTreeView treeView;
        QString rootDir;

    signals:
        void fileSelected(QString const &dir);
        
    public slots:
        void slotRootDirSelect();
    
};














#endif // FILESELECTOR_HPP
