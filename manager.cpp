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
    fixCamera    = 0;
    actualCamera = 0;
    mainproject  = 0;

    keycontrol = CameraControl;
}

/*
 * Initiate the main classes
 *
 * *************************************************/
void Manager::Init() {

    freeCamera   = new Camera();                 // Opengl camera matirx for viewing
    fixCamera    = new Camera();
    actualCamera = fixCamera;

    ptreeview   = new ProjectTreeView ();
    mainwindow  = new MainWindow( *this );
    mainproject = new Project   ( *this );      // Proejct for contain data for .....
    QObject::connect (ptreeview, SIGNAL(clicked(QModelIndex)), mainproject, SLOT(treeCliked(QModelIndex)));

    factory = new Obj3dFactory ( mainproject);
    mainwindow->show();
    mainproject->initGlpart ( (mainwindow->getMainGLW()) );
}

Manager::~Manager () {
    delete freeCamera;
    delete fixCamera;
    delete mainproject;
    delete ptreeview;
}


bool Manager::eventFilter(QObject* object,QEvent* event) {

    bool processed = false;
    if(event->type() == QEvent::KeyPress) {
        if ( keycontrol == Manager::ItemControl ) {
             processed = mainproject->keyEvent( ( QKeyEvent * ) event);
        } else {
             processed = freeCamera->keyEvent(( QKeyEvent * ) event );
        }
        if ( processed ) { return true; }
    }
    return QObject::eventFilter(object,event);
}


/*
 *
 * */
GLWidget & Manager::getMainGLW () {
    return mainwindow->getMainGLW();
}


