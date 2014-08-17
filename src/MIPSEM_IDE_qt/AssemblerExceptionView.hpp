#ifndef ASSEMBLEREXCEPTIONVIEW_HPP
#define ASSEMBLEREXCEPTIONVIEW_HPP

#include "MIPSEMcore/Exceptions.hpp"

#include <vector>

#include <QListWidget>
#include <QStandardItem>
#include <QStandardItemModel>


class AssemblerExceptionView : public QListWidget{
    Q_OBJECT
    
    public:
        AssemblerExceptionView(QWidget *parent = NULL);
        
        vector<AssemblerException> assemblerExceptions;
        void setAssemblerExceptionList(vector<AssemblerException> const &list);
        
    signals:
        void programLineSelected(ProgramLine const &exception);
        
        
    public slots:
        void slotListItemSelected(QListWidgetItem *item);
        
};










#endif // ASSEMBLEREXCEPTIONVIEW_HPP
