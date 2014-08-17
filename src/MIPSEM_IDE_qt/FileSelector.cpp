#include "FileSelector.hpp"

#include <QFileDialog>
#include <QInputDialog>

FileSelector::FileSelector(QWidget *parent)
    :   QWidget(parent)
{
    
    layout = new QGridLayout(this);
    
    //buttons
    buttonRootDirSelect = new QPushButton();
    buttonRootDirSelect->setText("root directory");
    buttonRootDirSelect->setStyleSheet("font-weight:bold");
    connect(buttonRootDirSelect, SIGNAL(clicked()), 
            this, SLOT(slotRootDirSelect()));
    layout->addWidget(buttonRootDirSelect, 0, 0, 1, 3);
       
    newDirAction = new QAction(this);
    newDirAction->setText("new directory");
    buttonNewMenu = new QMenu();
    buttonNewMenu->addAction(newDirAction);
    connect(newDirAction, SIGNAL(triggered()), 
            this, SLOT(slotNewDir()));
    
    newFileAction = new QAction(this);
    newFileAction->setText("new file");
    buttonNewMenu->addAction(newFileAction);
    connect(newFileAction, SIGNAL(triggered()), 
            this, SLOT(slotNewFile()));
    
    buttonNew = new QToolButton;
    buttonNew->setText("+");
    buttonNew->setStyleSheet("font-weight:bold");
    buttonNew->setMenu(buttonNewMenu);
    buttonNew->setPopupMode(QToolButton::InstantPopup);
    
    layout->addWidget(buttonNew, 0, 3, 1, 1);
    
    //treeView
    rootDir = QDir::currentPath();
    fileSystemModel = new QFileSystemModel();
    fileSystemModel->setRootPath(rootDir);
    
    treeView = new QTreeView();
    treeView->setModel(fileSystemModel);
    //remove the 3 columns after "Name" in file viewer
    for(int i=1; i<=3; i++){
       treeView->hideColumn(i);
    }
    
    // Demonstrating look and feel features
    treeView->setAnimated(false);
    treeView->setIndentation(10);
    treeView->setSortingEnabled(true);
    
    connect(treeView, SIGNAL(doubleClicked(QModelIndex const &)), 
            this, SLOT(slotTreeViewIndexSelected(QModelIndex const &)));
    
    layout->addWidget(treeView, 1, 0, 1, 4);
    
}
FileSelector::~FileSelector(){
    delete
    layout,
        buttonRootDirSelect,
        buttonNew,
            buttonNewMenu,
                newDirAction,
                newFileAction,
        treeView,
            fileSystemModel
    ;
}

void FileSelector::slotRootDirSelect(){
    rootDir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 rootDir,
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    fileSystemModel->setRootPath(rootDir);
    treeView->setRootIndex(fileSystemModel->index(rootDir));
}

void FileSelector::slotTreeViewIndexSelected(QModelIndex const &index){
    QFileInfo info = fileSystemModel->fileInfo(index);
    if(info.isFile()){
        //file double clicked!
        QString fileName = info.absoluteFilePath();
        emit fileSelected(fileName);
    }
}

void FileSelector::slotNewDir(){
    QString dirName = QFileDialog::getExistingDirectory(this, tr("Open file"),
                                                    rootDir);
    QDir dir;
    dir.mkpath(dirName);
}

void FileSelector::slotNewFile(){
    QString fileName = QFileDialog::getSaveFileName(this, 
                                                    tr("Open file"),
                                                    rootDir);
    if(!fileName.isEmpty()){
        QFile newFile(fileName);
        newFile.resize(0);
    }
}




































