#include <QtWidgets>


#include "FileBrowser.hpp"
#include "FileEditor.hpp"
#include "FileSelector.hpp"
#include "TabbedFileEditor.hpp"


int main(int argv, char **args){
    QApplication app(argv, args);
    QString programDir = app.applicationDirPath() + QString("/");

    FileBrowser browser = FileBrowser();
    browser.show();
    
    return app.exec();
}




























