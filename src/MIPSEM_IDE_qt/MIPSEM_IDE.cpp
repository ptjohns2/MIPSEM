#include "MIPSEM_IDE.hpp"



MIPSEM_IDE::MIPSEM_IDE(QWidget *parent)
    :   QWidget(parent)
{
    layout = new QGridLayout(this);
    
    middle = new QSplitter(Qt::Horizontal);
    fileSelector = new FileSelector();
    middle->addWidget(fileSelector);
    tabbedFileEditor = new TabbedFileEditor();
    middle->addWidget(tabbedFileEditor);
    
    middle->setStretchFactor(1, 1);
    middle->setStretchFactor(0, 0);
    connect(fileSelector, SIGNAL(fileSelected(QString const &)), 
            tabbedFileEditor, SLOT(editFile(QString const &)));

    bottom = new QSplitter(Qt::Vertical);
    bottom->addWidget(middle);
    assemblerExceptionView = new AssemblerExceptionView();    
    bottom->addWidget(assemblerExceptionView);
    bottom->setStretchFactor(1, 0);
    bottom->setStretchFactor(0, 1);
    connect(assemblerExceptionView, SIGNAL(programLineSelected(const ProgramLine)),
            tabbedFileEditor, SLOT(selectFileLine(const ProgramLine)));
    layout->addWidget(bottom);
    
    
    
    
    
    ProgramLine line1;
    line1.fileName = "D:\\tmp\\test1.txt";
    line1.lineNumber = 2;
    line1.text = "line2text";
    AssemblerException e1 = AssemblerException(line1, "ERROR1", "badtoken1");
    
    ProgramLine line2;
    line2.fileName = "D:\\tmp\\test2.txt";
    line2.lineNumber = 11;
    line2.text = "text11";
    AssemblerException e2 = AssemblerException(line2, "ERROR2", "badToken2");
    vector<AssemblerException> vect;
    vect.push_back(e1);
    vect.push_back(e2);
    
    assemblerExceptionView->setAssemblerExceptionList(vect);
    
    
}

MIPSEM_IDE::~MIPSEM_IDE(){
    delete 
    layout;
        middle,
            tabbedFileEditor,
            fileSelector,
        bottom,
            assemblerExceptionView
    ;
}























