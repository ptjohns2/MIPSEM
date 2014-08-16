#include <QtWidgets>

#include "AssemblerExceptionView.hpp"
#include "FileBrowser.hpp"
#include "FileEditor.hpp"
#include "FileSelector.hpp"
#include "TabbedFileEditor.hpp"


int main(int argv, char **args){
    QApplication app(argv, args);
    QString programDir = app.applicationDirPath() + QString("/");
/*
    FileBrowser browser = FileBrowser();
    browser.show();
  */
    
    AssemblerExceptionView view = AssemblerExceptionView();
    
    ProgramLine line1;
    line1.fileName = "testFile";
    line1.lineNumber = 2;
    line1.text = "TEST TEXT CONTENTS";
    AssemblerException e1 = AssemblerException(&line1, "ERROR1", "badtoken1");
    
    ProgramLine line2;
    line2.fileName = "program.txt";
    line2.lineNumber = 54;
    line2.text = "textttt";
    AssemblerException e2 = AssemblerException(&line2, "ERROR2", "badToken2");
    vector<AssemblerException> vect;
    vect.push_back(e1);
    vect.push_back(e2);
    
    view.setAssemblerExceptionList(vect);
    
    view.show();
    
            
    return app.exec();
}




























