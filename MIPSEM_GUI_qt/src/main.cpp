#include <QtWidgets>



#include "FileEditor.hpp"
#include "TabbedFileEditor.hpp"


int main(int argv, char **args){
    QApplication app(argv, args);
   
    QString programDir = app.applicationDirPath() + QString("/");
    
    
    TabbedFileEditor editor = TabbedFileEditor();
    editor.editFile(programDir + "program1.txt");
    editor.editFile(programDir + "program2.txt");
    editor.editFile(programDir + "program3.txt");
    
    //editor.editFile(programDir + "program2.txt");
    
    editor.show();
    
    return app.exec();
}




























