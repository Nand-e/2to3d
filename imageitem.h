#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include "objectItem.h"
#include "opencv2/highgui/highgui.hpp"


#include <QString>

class ImageItem : public ObjectItem
{
public:
    ImageItem( const QString data, const QString file,  ObjectItem * parentItem );


    // This inmplemented in Empty Item
    virtual QVector3D & getPosition ();
    virtual QVector3D & getScale();
    virtual QMatrix4x4 getMatrix();
    virtual bool manipulate (QKeyEvent *event);
    virtual void step (QVector3D & vect);
    virtual void  drawgl ( GLWidget  &gl, QMatrix4x4 &mat );
    virtual void takeTexture ();
    virtual std::string getType() const;
    virtual bool saveToFile  (std::ofstream & of );
    virtual bool loadFromFile(std::ifstream & ifs);

    bool initPicture ();

    QString filename;
    unsigned int glID;
    cv::Mat picture;                      // background image


};

#endif // IMAGEITEM_H
