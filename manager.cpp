#include "manager.h"

#include "camera.h"
#include "project.h"
#include "projecttreeview.h"
#include "mainwindow.h"
#include "obj3dfactory.h"
#include <QEvent>


/*
 * Contanier for global daata
 *
 * ************************************************/

Manager::Manager()
{
    freeCamera       = 0;
    actualCamera     = 0;
    mainproject      = 0;
    keycontrol       = CameraControl;
}

/*
 * Initiate the main classes
 *
 * *************************************************/
void Manager::Init() {

    freeCamera  = new Camera();                       // Opengl camera matirx for viewing
    ptreeview   = new ProjectTreeView (0, *this );
    mainproject = new Project   ( *this );            // Proejct for contain data for .....
    mainwindow  = new MainWindow( *this );

    QObject::connect (ptreeview, SIGNAL(clicked(QModelIndex)), mainproject, SLOT(treeCliked(QModelIndex)));

    factory = new Obj3dFactory ( mainproject );
    mainwindow->show();
    mainproject->initGlpart ( (mainwindow->getMainGLW()) );
}

Manager::~Manager () {
    delete freeCamera;
    delete mainproject;
    delete ptreeview;
}





/*
 *
 * */
GLWidget & Manager::getMainGLW () {
    return mainwindow->getMainGLW();
}


