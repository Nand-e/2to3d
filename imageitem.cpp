#include "imageitem.h"

#include "opencv2/imgproc/imgproc.hpp"

#include <QVector3D>
#include <QMatrix4x4>

#include "project.h"
#include "glwidget.h"
#include "manager.h"

ImageItem::ImageItem(const QString data, const QString filename1, ObjectItem * parentItem, Project & pro1) :
    pro ( pro1 ), ObjectItem (data, parentItem )
{
    filename = filename1;
    glID = 0;

}

ImageItem::~ImageItem () {
    if ( glID != 0 ) {
         GLWidget & gl = pro.getManger().getMainGLW();
         gl.glDeleteTextures(1, &glID);
    }
    qDebug()<< "Delete Image";
    //delete Camera ();
}

Camera * ImageItem::getCamera() {
    return & imageCam;
}

bool ImageItem::initPicture() {

    picture = cv::imread( filename.toStdString() );
    if(! picture.data ) {
        qDebug() <<  "Could not open or find the image: " << filename;
        return false;
    }
    cv::cvtColor( picture, picture, CV_BGR2RGB);
    GLWidget & gl = pro.getManger().getMainGLW();
    float w,h;
    w = picture.cols;
    h = picture.rows;

    if ( glID  == 0 ) { gl.glGenBuffers( 1, &glID ); }

    gl.glBindTexture ( GL_TEXTURE_2D , glID);
    gl.glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB,
                     GL_UNSIGNED_BYTE, ( GLvoid * ) picture.data );
    qDebug() << "Generate Texture for BAckground, id:" << glID;
    gl.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    gl.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    gl.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gl.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    float aspectratio = w / h;
    float x = 1 * aspectratio;

    faceVertex.append ( QVector3D ( -x , 1 , 0 ));        // Make face
    faceVertex.append ( QVector3D ( -x ,-1 , 0 ));
    faceVertex.append ( QVector3D (  x ,-1 , 0 ));
    faceVertex.append ( QVector3D (  x , 1 , 0 ));

    faceTex.append ( QVector2D ( 0,0) );                  // Set Texture coordinate
    faceTex.append ( QVector2D ( 0,1) );
    faceTex.append ( QVector2D ( 1,1) );
    faceTex.append ( QVector2D ( 1,0) );

    return true;
}


std::string ImageItem::getType() const  {
    return std::string ("IMAGE");
}

bool ImageItem::saveToFile  (std::ofstream & of ) {
    of << getType() << std::endl;                                       // type
    of << filename.toStdString()  << std::endl;                         // filename
   /*
    of << pos.x() << "," << pos.y() << "," << pos.z() << std::endl;     // pos
    for ( int i=0; i  <3 ; i++ ) {
        of << imageCam..column(i).x() << ",";                   // rotation
        of << imageCam.rotation.column(i).y() << ",";
        of << imageCam.rotation.column(i).z() ;
        of << std::endl;
    }*/
    return true;
}
bool ImageItem::loadFromFile(std::ifstream & ifs) {
    std::string str;
    std::getline(ifs, str );
    filename = str.c_str() ;
    this->m_itemData = filename;
    return true;
}


QVector3D & ImageItem:: getPosition () { return QVector3D (); }
QVector3D & ImageItem:: getScale()     { return QVector3D (); }
QMatrix4x4  ImageItem:: getMatrix()    { return QMatrix4x4(); }

void ImageItem::drawgl ( GLWidget  &gl, QMatrix4x4 &mat ) {};
bool ImageItem::manipulate (QKeyEvent *event) { return false; }
void ImageItem::step (QVector3D & vect) {  };
void ImageItem::takeTexture () {};
