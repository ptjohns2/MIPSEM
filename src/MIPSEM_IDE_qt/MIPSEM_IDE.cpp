#include "MIPSEM_IDE.hpp"



MIPSEM_IDE::MIPSEM_IDE(QWidget *parent)
    :   QSplitter(parent), fileEditSection(Qt::Horizontal)
      //tabbedFileEditor(), fileSelector()
{
    fileEditSection.addWidget(&fileSelector);
    fileEditSection.addWidget(&tabbedFileEditor);
    fileEditSection.setStretchFactor(1, 1);
    fileEditSection.setStretchFactor(0, 0);
    this->setOrientation(Qt::Vertical);
    this->addWidget(&fileEditSection);
    this->addWidget(&assemblerExceptionView);
    
    this->setStretchFactor(1, 0);
    this->setStretchFactor(0, 1);
    connect(&fileSelector, SIGNAL(fileSelected(QString const &)), &tabbedFileEditor, SLOT(editFile(QString const &)));
    
    
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
    
    assemblerExceptionView.setAssemblerExceptionList(vect);
    
    
    connect(&assemblerExceptionView, SIGNAL(programLineSelected(const ProgramLine)),
            &tabbedFileEditor, SLOT(selectFileLine(const ProgramLine)));
    
}
