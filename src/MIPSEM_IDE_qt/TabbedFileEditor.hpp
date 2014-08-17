#ifndef TabbedFileEditor_HPP
#define TabbedFileEditor_HPP

#include "FileEditor.hpp"
#include "AssemblerExceptionView.hpp"

#include <QTabWidget>
#include <QSplitter>
#include <QBoxLayout>


class TabbedFileEditor : public QTabWidget{
    Q_OBJECT
   
    public:
        TabbedFileEditor(QWidget *parent = NULL);    
        ~TabbedFileEditor();
        
        bool hasFileOpen(QString const &dir);
        void focusOnFile(QString const &dir);
        FileEditor* getDirectoryFileEditor(QString const &dir);
        bool requestCloseTab(int index);
        bool requestCloseAllTabs();
        
        vector<FileEditor*> editors;
        
    public slots:
        void editFile(QString const &dir);
        void selectFileLine(ProgramLine const &programLine);
        void slotRequestCloseTab(int index);
        
        
};









#endif // TabbedFileEditor_HPP
