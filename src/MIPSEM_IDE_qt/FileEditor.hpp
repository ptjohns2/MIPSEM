#ifndef FileEditor_HPP
#define FileEditor_HPP

#include "MIPS32SyntaxHighlighter.hpp"

#include <QPlainTextEdit>
#include <QPaintEvent>
#include <QShortcut>

class FileEditor : public QPlainTextEdit{
    Q_OBJECT   
    
    public:
        FileEditor(QString const &dir, QWidget *parent = NULL);
        void init();
        void init_pointers(); 
        ~FileEditor();
        void deinit();
        
        QString dir;
        bool saveFile();
        QString lastSavedContents;
        bool requestSave();
        bool readFile(QString const &dir);
        bool modifiedSinceLastSave();
        QShortcut *shortcutSave;
        
        void selectLine(unsigned int lineNum);
        
    signals:
        void signalRefreshSyntaxHighlighter();
        
    public slots:
        void refreshSyntaxHighlighter();
        void slotSaveFile();
        void highlightCurrentLine();
        
    protected:
       virtual void	paintEvent(QPaintEvent *event);
       virtual void wheelEvent(QWheelEvent *event);
        
        
    private:
        MIPS32SyntaxHighlighter *highlighter;
};









#endif // FileEditor_HPP
