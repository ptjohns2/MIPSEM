#ifndef FILESELECTOR_HPP
#define FILESELECTOR_HPP

#include <QGridLayout>
#include <QFileSystemModel>
#include <QToolButton>
#include <QMenu>
#include <QPushButton>
#include <QSplitter>
#include <QTextEdit>
#include <QTreeView>

class DirectorySelector : public QWidget{
    Q_OBJECT
    
    public:
        DirectorySelector(QWidget *parent = NULL);    
  
        QTextEdit *directoryEdit;
        QPushButton *directorySelect;
        
    signals:
        void directorySelected(QString const &dir);    
        
        
};

class FileSelector : public QWidget{
    Q_OBJECT
    
    public:
        FileSelector(QWidget *parent = NULL);
        void init();
        void init_pointers();
        ~FileSelector();
        void deinit();
        
        QGridLayout *layout;
        
        QPushButton *buttonRootDirSelect;
        QToolButton *buttonNew;
            QMenu *buttonNewMenu;
            QAction *newDirAction;
            QAction *newFileAction;
            
        QTreeView *treeView;
            QFileSystemModel *fileSystemModel;
        
        
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
