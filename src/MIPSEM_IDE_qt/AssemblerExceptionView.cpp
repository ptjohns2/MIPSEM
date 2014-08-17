#include "AssemblerExceptionView.hpp"



AssemblerExceptionView::AssemblerExceptionView(QWidget *parent)
    :   QListWidget(parent)
{
    connect(this, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(slotListItemSelected(QListWidgetItem*)));
}



void AssemblerExceptionView::setAssemblerExceptionList(vector<AssemblerException> const &list){
    this->clear();
    assemblerExceptions.clear();
    for(int i=0; i<list.size(); i++){
        assemblerExceptions.push_back(list[i]);
        std::string str = assemblerExceptions[i].toString();
        QString lineString(str.c_str());
        this->addItem(lineString);
    }   
    this->show();
}


void AssemblerExceptionView::slotListItemSelected(QListWidgetItem *item){
    int index = this->row(item);
    ProgramLine const line = assemblerExceptions[index].programLine;
    emit programLineSelected(line);
}
