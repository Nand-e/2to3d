#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include "objectItem.h"
#include "opencv2/highgui/highgui.hpp"

class Project;

#include "camera.h"
#include <QString>

class ImageItem : public ObjectItem
{
public:
    ImageItem(const QString data, const QString filename,  ObjectItem * parentItem, Project &pro  );
    ~ImageItem ();

    // This inmplemented in Empty Item
    virtual QVector3D & getPosition ();
    virtual QVector3D & getScale();
    virtual QMatrix4x4 getMatrix();
    virtual bool manipulate (QKeyEvent *event);
    virtual void step   ( QVector3D & vect );
    virtual void drawgl ( GLWidget  &gl, QMatrix4x4 &mat );
    virtual void takeTexture ();
    virtual std::string getType() const;
    virtual bool saveToFile  (std::ofstream & of );
    virtual bool loadFromFile(std::ifstream & ifs);

    bool initPicture ();
    Camera * getCamera ();
    unsigned int glID;

    QVector<QVector3D> faceVertex;                                          // background image object vertex
    QVector<QVector2D> faceTex;

private:
    QString filename;
    Camera  imageCam;

    cv::Mat picture;                      // background image

    Project & pro;
};

#endif // IMAGEITEM_H
