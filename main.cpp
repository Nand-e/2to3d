/****************************************************************************
**

****************************************************************************/

#include <QApplication>

#include "Mainwindow.h"
#include "Globals.h"

Manager * manager;


int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(textures);
    QApplication app(argc, argv);

    manager = new Manager ();               // Contain main classes and controll them
    manager->Init();                        // Init main classes
    app.installEventFilter(manager->mainproject);
    return app.exec();
}
