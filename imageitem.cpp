#include "imageitem.h"

#include "opencv2/imgproc/imgproc.hpp"

#include <QVector3D>
#include <QMatrix4x4>

ImageItem::ImageItem(const QString data, const QString file, ObjectItem * parentItem = 0) :
    ObjectItem (data, parentItem )
{
    filename = file;
}

bool ImageItem::initPicture() {
    this->picture = cv::imread( filename.toStdString() );
    if(! picture.data ) {
        qDebug() <<  "Could not open or find the image: " << filename;
        return false;
    }
    cv::cvtColor( picture, picture, CV_BGR2RGB);
    //int w,h;
    //w = actualBackground.cols;
    //h = actualBackground.rows;
    return true;
}


QVector3D & ImageItem:: getPosition () { return  QVector3D (); }
QVector3D & ImageItem:: getScale()     { return  QVector3D (); }
QMatrix4x4 ImageItem:: getMatrix()     { return QMatrix4x4 (); }

bool ImageItem::manipulate (QKeyEvent *event) { return false; }
void ImageItem::step (QVector3D & vect) {  };
void ImageItem::takeTexture () {};

std::string ImageItem::getType() const  {
    return std::string ("Picture");
}

void ImageItem::drawgl ( GLWidget  &gl, QMatrix4x4 &mat )  {};
bool ImageItem::saveToFile  (std::ofstream & of ) { return true; };
bool ImageItem::loadFromFile(std::ifstream & ifs) { return true; };
