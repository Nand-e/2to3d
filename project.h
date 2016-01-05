#ifndef PROJECT_H
#define PROJECT_H

#include <string>

#include "opencv/highgui.h"

#include <Qvector>
#include <QVector3D>
#include <QModelIndex>
#include <QObject>
#include <QMouseEvent>

/*
 * Holds the preject specific information such a
 * image and 3d objects, etc ...... .
 * */

class TreeModel;
class GLWidget;
class QMatrix4x4;
class QKeyEvent;
class Manager;
class ObjectItem;
class ImageItem;



class Project : public QObject
{
    Q_OBJECT
public:
    Project( Manager & m);
    Project::~Project();

    void clearProject();
    void createRoots ();


    void initGlpart     ( GLWidget &gl );
    void drawObjects    ( GLWidget &glw);
    void drawBackground ( GLWidget &glw) ;
    void aspectChanged  ( float aspect );

    void addImage  ();                          // Add new elemet to project and update the view
    void addObject (ObjectItem * newItem);      // Add new elemet to project and update the view
    void deleteObject (ObjectItem * item );


    Manager & getManger();

    bool saveToFile ( QString & filename );
    bool loadFile(QString &filename);
    bool saveImagesData (  std::ofstream & of );
    bool saveChildren (int parentid, int & level, ObjectItem *obj,  std::ofstream & str );

    void setFreecam ( bool c ) { freecam = c; }

    void mouseEvent      ( QMouseEvent * event );
    void mousePressEvent ( QMouseEvent * event );
    bool keyEvent        ( QKeyEvent * event);
    bool eventFilter     ( QObject * object, QEvent * event);

public slots:
    void treeCliked   ( QModelIndex index);
    void setViewAngle ( int va);



//private: not private for test
public:
    TreeModel  * const container;                          // data Container for project data

    ObjectItem * imagesRoot;
    ObjectItem * objectRoot;

    ImageItem  * actualImage;
    ObjectItem * actualobject;

private:

    bool    freecam;
    bool    renderEnable;
    float   viewportAspect;
    QPoint  lastPos;
    Manager & man;
    void    drawHelper (ObjectItem *obj, GLWidget &glw, QMatrix4x4 camp);

    QVector<QVector3D> faceVertex;                                          // background image object vertex
    QVector<QVector2D> faceTex;
};


#endif // PROJECT_H
