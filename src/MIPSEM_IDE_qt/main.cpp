#include <QtWidgets>

#include "AssemblerExceptionView.hpp"
#include "FileEditor.hpp"
#include "FileSelector.hpp"
#include "MIPSEM_IDE.hpp"
#include "TabbedFileEditor.hpp"


int main(int argv, char **args){
    QApplication app(argv, args);
    QString programDir = app.applicationDirPath() + QString("/");

    MIPSEM_IDE browser = MIPSEM_IDE();
    browser.resize(800, 500);
    browser.show();
       
    return app.exec();
}




























