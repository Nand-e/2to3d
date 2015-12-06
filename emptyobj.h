#ifndef EMPTYOBJ_H
#define EMPTYOBJ_H


#include <QVector>
#include <QVector3D>
#include <QVector2D>
#include <QImage>
#include <QMatrix>

#include "opencv2/highgui/highgui.hpp"

#include <fstream>
#include <iostream>

#include "glwidget.h"
#include "objectItem.h"

class QKeyEvent;
class QMatrix4x4;
class QPixmap;


class EmptyObj : public ObjectItem {

public:
    EmptyObj(const QString data, ObjectItem *parent = 0);
    ~EmptyObj ();

    virtual bool manipulate (QKeyEvent *event);              // Manipulate Item byKey (etc....)
    virtual QMatrix4x4 getMatrix();
    virtual QVector3D & getPosition();
    virtual QVector3D & getScale ();


// private: public only for test
    unsigned int textureID;                                  // GPU Texture ID
    cv::Mat * textureMat;                                    // Texture in cpu memroy as cv Mat
    QPixmap   textPixmap;                                    // Shared memory with cv Mat ( GUI porpose )

    QVector3D  pos, rot, scale;
    QMatrix4x4 rotation;
    QVector<QVector3D>  vertices;                            // Item verticies for object
    QVector<QVector2D>  texCoords;                           // Texture coordinates // TO DO need to b

protected:

    virtual void rotate ( QVector3D & axis, float angle );
    virtual void step   ( QVector3D & vect );

    void   UvtoCvCoordinate (cv::Mat *input, cv::Point2f * output );    //
    QImage cvMatToQImage    ( const cv::Mat &inMat );
};

#endif // EMPTYOBJ_H
