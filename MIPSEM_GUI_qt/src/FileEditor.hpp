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
        ~FileEditor();
        
        QString dir;
        bool saveFile();
        QString lastSavedContents;
        bool requestSave();
        bool readFile(QString const &dir);
        bool modifiedSinceLastSave();
        QShortcut *shortcutSave;
        
    signals:
        void signalRefreshSyntaxHighlighter();
        
    public slots:
        void refreshSyntaxHighlighter();
        void slotSaveFile();
        
    protected:
       virtual void	paintEvent(QPaintEvent *event);
       virtual void wheelEvent(QWheelEvent *event);
        
        
    private:
        MIPS32SyntaxHighlighter *highlighter;
};









#endif // FileEditor_HPP
