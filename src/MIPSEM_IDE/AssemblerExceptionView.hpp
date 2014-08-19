#ifndef ASSEMBLEREXCEPTIONVIEW_HPP
#define ASSEMBLEREXCEPTIONVIEW_HPP

#include "MIPSEM_CORE/Exceptions.hpp"

#include <vector>

#include <QListWidget>
#include <QStandardItem>
#include <QStandardItemModel>


class AssemblerExceptionView : public QListWidget{
    Q_OBJECT
    
    public:
        AssemblerExceptionView(QWidget *parent = NULL);
        class LineItem{
            public:   
                LineItem(){}
                AssemblerException assemblerException;
                bool isAssemblerException;
                QString text;
        };
        vector<LineItem> lineItems;
        void setAssemblerExceptionList(vector<AssemblerException> const &list);
        
        void addAssemblerExceptionLine(AssemblerException assemblerException);
        void addTextLine(QString const &text);
        
        void clearAssemblerExceptions();
        
    signals:
        void programLineSelected(ProgramLine const &exception);
        
        
    public slots:
        void slotListItemSelected(QListWidgetItem *item);
        
};










#endif // ASSEMBLEREXCEPTIONVIEW_HPP
