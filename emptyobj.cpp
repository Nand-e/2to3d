#include "emptyobj.h"

// open cv headers
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

// Qt headers
#include <QKeyEvent>
#include <QMatrix4x4>
#include <QGLWidget>
#include <QOpenGLFunctions>
#include <QGLShaderProgram>
#include <QString>

// Standard headers
#include <string>
#include <fstream>
#include <stack>

// own headers
#include "Globals.h"            // TODO
#include "objectItem.h"
#include "glwidget.h"           // TODO
#include "mainwindow.h"         // TODO

#include "emptyobj.h"


#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_TEXCOORD_ATTRIBUTE 1

EmptyObj::EmptyObj(const QString name, ObjectItem *parent) :
    ObjectItem( name , parent)
{
    rotation.setToIdentity();
    pos   = QVector3D ( 0, 0, 0 );
    rot   = QVector3D ( 0, 0, 0 );
    scale = QVector3D ( 1, 1, 1 );
    textureID = 0;

}

EmptyObj::~EmptyObj() {
    qDebug() << "delet EmptyObj";
}


QVector3D & EmptyObj::getPosition() {
    return this->pos;
}

QVector3D & EmptyObj::getScale () {
    return this->scale;
}

QMatrix4x4 EmptyObj::getMatrix() {
    QMatrix4x4 mat;
    mat.setToIdentity();
    mat.translate(pos);
    mat *= rotation;
    return mat;
}

void EmptyObj::step(QVector3D &vect) {
    pos += vect;
}

void EmptyObj::rotate (QVector3D & axis, float angle ) {
    QMatrix4x4 mat1;
    mat1.rotate(angle, axis);
    this->rotation *= mat1;
}

bool EmptyObj::manipulate( QKeyEvent *event ) {

    bool processed = true;
    if ( event->type() == QKeyEvent::KeyPress) {
    switch ( event->key() ) {
        case Qt::Key_W:
            step ( QVector3D ( 0,0,-0.05f)); break;
        case Qt::Key_S:
            step ( QVector3D ( 0,0, 0.05f)); break;
         case Qt::Key_A:
            step ( QVector3D ( -0.05f,0,0)); break;
        case Qt::Key_D:
            step ( QVector3D ( 0.05f,0,0 ) ); break;
        case Qt::Key_Q:
            step ( QVector3D ( 0,0.05f,0 ) ); break;
        case Qt::Key_Y:
            step ( QVector3D ( 0,-0.05f,0 ) ); break;
        case Qt::Key_Left:
             rotate( QVector3D (0,1,0), 1);
             rot += QVector3D ( 0,1,0);
             break;
        case Qt::Key_Right:
             rotate( QVector3D (0,1,0), -1);
             rot += QVector3D ( 0,-1,0);
             break;
        case Qt::Key_Up:
             rotate( QVector3D (1,0,0), 1);
             rot += QVector3D ( 1,0,0);

             break;
        case Qt::Key_Down:
             rotate( QVector3D (1,0,0), -1);
             rot += QVector3D ( -1,0,0);

             break;
        case Qt::Key_Plus:
             rotate( QVector3D (0,0,1), 1);
             rot += QVector3D ( 0,0,1);

             break;
        case Qt::Key_Minus:
             rotate( QVector3D (0,0,1), -1);
             rot += QVector3D ( 0,0,-1);
             break;

        case Qt::Key_PageUp:
             scale +=  QVector3D ( 0, 0.05f , 0);
             break;
        case Qt::Key_PageDown:
             scale +=  QVector3D ( 0, -0.05f , 0);
             break;

        case Qt::Key_Home:
             scale +=  QVector3D ( 0.05f, 0 , 0);
             break;
        case Qt::Key_End:
             scale +=  QVector3D ( -0.05f, 0 , 0);
             break;
        case Qt::Key_Delete:
             scale +=  QVector3D ( 0,0, 0.05f );
             break;
        case Qt::Key_Insert:
             scale +=  QVector3D ( 0,0, -0.05f );
             break;
        default:
            processed = false;
        }
    }
    return processed;
}

void EmptyObj::UvtoCvCoordinate (cv::Mat * input, cv::Point2f * output) {
    unsigned int w,h;
    w = input->cols;
    h = input->rows;
    for ( int i = 0; i < 4 ; i ++ ) {
        output[i] = cv::Point2f( texCoords.at(i).x()  *w, texCoords[i].y() * h );
    }
}

QImage EmptyObj::cvMatToQImage( const cv::Mat &inMat )
   {
      switch ( inMat.type() )
      {
         // 8-bit, 4 channel
         case CV_8UC4:
         {
            QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB32 );
            return image;
         }

         // 8-bit, 3 channel
         case CV_8UC3:
         {
            QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB888 );
            return image.rgbSwapped();
         }

         // 8-bit, 1 channel
         case CV_8UC1:
         {
            static QVector<QRgb>  sColorTable;

            // only create our color table once
            if ( sColorTable.isEmpty() )
            {
               for ( int i = 0; i < 256; ++i )
                  sColorTable.push_back( qRgb( i, i, i ) );
            }

            QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_Indexed8 );

            image.setColorTable( sColorTable );

            return image;
         }

         default:
            qWarning() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
            break;
      }

      return QImage();
}


