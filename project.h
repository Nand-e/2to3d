#ifndef PROJECT_H
#define PROJECT_H

#include <string>

#include "opencv/highgui.h"

#include <Qvector>
#include <QVector3D>
#include <QModelIndex>
#include <QObject>

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



class Project : public QObject
{
    Q_OBJECT
public:
    Project( Manager & m);
    Project::~Project();

    void clearProject();
    void createRoots ();

    bool keyEvent       (QKeyEvent*event);
    void initGlpart     (GLWidget &gl );
    void drawObjects    (GLWidget &glw);
    void drawBackground (GLWidget &glw) ;
    bool loadBackground (GLWidget & gl, QString name = "" );

    Manager & getManger();
    bool reLoadback ();
    bool saveToFile ();  
    bool loadFile();
    bool saveChildren (int parentid, int & level, ObjectItem *obj,  std::ofstream & str );


public slots:
    void treeCliked(QModelIndex index);

//private: not private for test
public:
    TreeModel  * container;                         // data Container for project data
    ObjectItem * actualobject;
    ObjectItem * imagesRoot;
    ObjectItem * objectRoot;
    unsigned int backtextID;    
    cv::Mat * actualBackground;                      // background image

private:
    QString imagename;
    bool    renderEnable;
    Manager & man;
    void    drawHelper (ObjectItem *obj, GLWidget &glw, QMatrix4x4 camp);

    QVector<QVector3D> faceVertex;                 // background image object vertex
    QVector<QVector2D> faceTex;
};


#endif // PROJECT_H
