#include "AssemblerExceptionView.hpp"



AssemblerExceptionView::AssemblerExceptionView(QWidget *parent)
    :   QListWidget(parent)
{    connect(this, SIGNAL(itemDoubleClicked(QListWidgetItem*)), 
             this, SLOT(slotListItemSelected(QListWidgetItem*)));
}



void AssemblerExceptionView::setAssemblerExceptionList(vector<AssemblerException> const &list){
    this->clear();
    lineItems.clear();
    addTextLine("Errors found: " + QString(std::to_string(list.size()).c_str()));
    for(int i=0; i<list.size(); i++){
        addAssemblerExceptionLine(list[i]);
    }   
    this->show();
}

void AssemblerExceptionView::addAssemblerExceptionLine(AssemblerException assemblerException){
    LineItem item;
    item.assemblerException = assemblerException;
    item.isAssemblerException = true;
    item.text = QString(assemblerException.toString().c_str());
    lineItems.push_back(item);
    this->addItem(item.text);
}

void AssemblerExceptionView::addTextLine(QString const &text){
    LineItem item;
    item.isAssemblerException = false;
    item.text = text;
    lineItems.push_back(item);
    this->addItem(item.text);
}



void AssemblerExceptionView::clearAssemblerExceptions(){
    lineItems.clear();
    this->clear();
    this->update();
}

void AssemblerExceptionView::slotListItemSelected(QListWidgetItem *item){
    int index = this->row(item);
    LineItem lineItem = lineItems[index];
    if(lineItem.isAssemblerException){
        emit programLineSelected(lineItem.assemblerException.programLine);
    }
}






