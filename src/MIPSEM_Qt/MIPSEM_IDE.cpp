#include "MIPSEM_IDE.hpp"

#include <QCoreApplication>
#include <QProcess>

MIPSEM_IDE::MIPSEM_IDE(QWidget *parent)
    :   QWidget(parent)
{
    init_pointers();
    init();
    
    QShortcut *shortcut = new QShortcut(QKeySequence("F5"), this);
    connect(shortcut, SIGNAL(activated()),
            this, SLOT(assembleOpenFile()));
    /*
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
    */
    
}
void MIPSEM_IDE::init(){
    layout->addWidget(toolbar);
   
    middle->addWidget(fileSelector);
    middle->addWidget(tabbedFileEditor);
    
    middle->setStretchFactor(1, 1);
    middle->setStretchFactor(0, 0);
    connect(fileSelector, SIGNAL(fileSelected(QString const &)), 
            tabbedFileEditor, SLOT(editFile(QString const &)));

    bottom->addWidget(middle);   
    bottom->addWidget(assemblerExceptionView);
    bottom->setStretchFactor(1, 0);
    bottom->setStretchFactor(0, 1);
    connect(assemblerExceptionView, SIGNAL(programLineSelected(const ProgramLine)),
            tabbedFileEditor, SLOT(selectFileLine(const ProgramLine)));
    
    layout->addWidget(bottom);

}

void MIPSEM_IDE::init_pointers(){
    layout = new QGridLayout(this);
        toolbar = new Toolbar();
        middle = new QSplitter(Qt::Horizontal);
            tabbedFileEditor = new TabbedFileEditor();
            fileSelector = new FileSelector();
        bottom = new QSplitter(Qt::Vertical);
            assemblerExceptionView = new AssemblerExceptionView();
}

MIPSEM_IDE::~MIPSEM_IDE(){
    deinit();
}
void MIPSEM_IDE::deinit(){
    delete 
    toolbar,
    layout,
        middle,
            tabbedFileEditor,
            fileSelector,
        bottom,
            assemblerExceptionView
    ;
}



void MIPSEM_IDE::assembleOpenFile(){
    if(!tabbedFileEditor->saveAllTabs()){
        assemblerExceptionView->clearAssemblerExceptions();
        return;
    }
    FileEditor* editor = (FileEditor*)tabbedFileEditor->currentWidget(); 
    if(editor == NULL){return;}
    QString dir = editor->dir;
    core.reset();
    bool validAssembly = core.assemble(dir.toStdString());
    if(!validAssembly){
        assemblerExceptionView->setAssemblerExceptionList(core.recoverableExceptions);   
    }else{
        assemblerExceptionView->clearAssemblerExceptions();
        assemblerExceptionView->addTextLine("> Assembly of \"" + dir + "\" successful.");
        assemblerExceptionView->addTextLine("Running object file \"" + QString(core.builtObjectFileName.c_str()) + "\"...");
        //QProcess *process = new QProcess(this);
        QString MIPSEM_IDE_filePath = QFileInfo(QCoreApplication::applicationFilePath()).filePath();
        QString MIPSEM_IDE_parentDirPath = QString(Parser::filePathToParentDirectory(MIPSEM_IDE_filePath.toStdString()).c_str());
        QString MIPSEM_CORE_filePath = MIPSEM_IDE_parentDirPath + "MIPSEM_CORE.exe";
        QStringList MIPSEM_CORE_arguments;
        MIPSEM_CORE_arguments << QString(core.builtObjectFileName.c_str());
        //QProcess *process = new QProcess();
        QString systemCall = "start " + MIPSEM_CORE_filePath + " " + MIPSEM_CORE_arguments[0];
        system(systemCall.toStdString().c_str());
    }
}



















