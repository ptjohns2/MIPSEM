#include <QtWidgets>



#include "FileEditor.hpp"
#include "FileSelector.hpp"
#include "TabbedFileEditor.hpp"


int main(int argv, char **args){
    QApplication app(argv, args);
    QString programDir = app.applicationDirPath() + QString("/");
    
    /*
    TabbedFileEditor editor = TabbedFileEditor();
    editor.resize(600, 600);
    editor.editFile(programDir + "program1.txt");
    editor.editFile(programDir + "program2.txt");
    editor.editFile(programDir + "program3.txt");
    
    editor.editFile(programDir + "program2.txt");
    
    editor.show();
    */
    
    FileSelector selector = FileSelector();
    selector.show();
    
    
    return app.exec();
}




























