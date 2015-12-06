#ifndef MANAGER_H
#define MANAGER_H

#include "camera.h"
#include "project.h"

class ProjectTreeView;
class MainWindow;
class QLWidget;
class Obj3dFactory;

class Manager : public QObject
{
    Q_OBJECT
public:
    enum KeyControl { CameraControl = 0, ItemControl, None    };
    Manager();    
    ~Manager ();
    GLWidget & getMainGLW ();                                   // give the mainwindow main glwidget back

    void Init();
    bool eventFilter(QObject* object,QEvent* event);

    void sedEdges ( bool e ) { edges = e; }

//private:

   Obj3dFactory    * factory;
   Camera          * actualCamera;
   Camera          * fixCamera;
   Camera          * freeCamera;        // 3D camera
   Project         * mainproject;   // Project container
   ProjectTreeView * ptreeview;     // Treeview for project data
   MainWindow      * mainwindow;
   KeyControl       keycontrol;


   bool edges;


};

#endif // MANAGER_H
