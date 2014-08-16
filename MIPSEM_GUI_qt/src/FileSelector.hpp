#ifndef FILESELECTOR_HPP
#define FILESELECTOR_HPP

#include <QGridLayout>
#include <QFileSystemModel>
#include <QToolButton>
#include <QMenu>
#include <QPushButton>
#include <QSplitter>
#include <QTreeView>

#define DEFAULT_DIR    ("")

class FileSelector : public QWidget{
    Q_OBJECT
    
    public:
        FileSelector(QWidget *parent = NULL);
        ~FileSelector();
        
        QGridLayout layout;
        
        QPushButton buttonRootDirSelect;
        QToolButton buttonNew;
        QMenu buttonNewMenu;
        QAction newDirAction;
        QAction newFileAction;
        
        QFileSystemModel fileSystemModel;
        QTreeView treeView;
        QString rootDir;

    signals:
        void fileSelected(QString const &dir);
        
        
    public slots:
        void slotRootDirSelect();
        void slotTreeViewIndexSelected(QModelIndex const &index);
        void slotNewDir();
        void slotNewFile();
    
};














#endif // FILESELECTOR_HPP
