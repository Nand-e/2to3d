#include "camera.h"

#include <QKeyEvent>

Camera::Camera()
{
    mat.setToIdentity();
    viewAngle = 45;
    mat0.perspective( viewAngle , 1 , 1 , 500 );
    pos = QVector3D ( 0, -2, -10);
    roty = rotx = 0;
}

Camera & Camera::operator = ( Camera & other ) {
    this->pos  = other.pos;
    this->mat0 = other.mat0;
    this->mat  = other.mat;
    this->rotx = other.rotx;
    this->roty = other.roty;
    return *this;
}

/*
 *
 *
 * Move Camera by key
 *******************************************************/
bool Camera::keyEvent (QKeyEvent *event) {
    bool processed = true;
    if ( event->type() == QKeyEvent::KeyPress) {
        switch ( event->key() ) {
            case Qt::Key_W:
                Step(0, 0.1f);  break;
            case Qt::Key_S:
                Step(0, -0.1f); break;
            case Qt::Key_A:
                Step( 1.0f, 0 ); break;
            case Qt::Key_D:
                Step( -1.0f, 0); break;
            case Qt::Key_Q:
                UpDown( 0.05f ); break;
            case Qt::Key_Y:
                UpDown( -0.05f ); break;
            default:
                processed = false;
            break;
        }
    }
    return processed;
}

void Camera::UpDown ( float sy) {
    pos+= QVector3D (0, -sy, 0);
}

void Camera::LeftRight(float sx) {
    pos-= QVector3D ( -sx,0 , 0);
}

void Camera::RotY ( float dt) {
    roty += dt;
}

void Camera::RotX ( float dt) {
    rotx += dt;
}

int Camera::getViewAngle () {
    return viewAngle;
}

void Camera::setViewAngle ( int  va ) {
    viewAngle = va;
    mat0.setToIdentity();
    mat0.perspective( ( float ) va , 1 , 1 ,100 );
   // qDebug() << mat0;
}

void Camera::Step(float x, float z) {

    QMatrix4x4 mat;
 //   mat.rotate( roty, 0, 1, 0 );
 //   mat.rotate( rotx, 1, 0, 0 );
    QVector3D vect = QVector3D ( 0 ,0 ,z) * mat;
    pos += vect;
  //  roty += x;
    //qDebug() << pos;
}

const QMatrix4x4 &Camera::getMatrix( float aspect ) {
    mat.setToIdentity();
    mat.perspective( viewAngle, aspect,1,500 );
    mat.translate(pos);
    mat.rotate( roty, 0, 1.0f ,0 );
    mat.rotate( rotx, 1, 0 ,0 );    
    return mat;
}


