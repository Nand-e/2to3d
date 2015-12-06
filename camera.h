#ifndef CAMERA_H
#define CAMERA_H

#include <QVector3D>
#include <QMatrix4x4>
class QKeyEvent;

class Camera : public QObject
{
    Q_OBJECT
public:
    Camera();    
    Camera & operator= ( Camera & other);
    int  getViewAngle ();

    bool keyEvent (QKeyEvent *event);
    void Step ( float x , float z);
    void UpDown (  float sy);
    void LeftRight (float sx );
    void RotY ( float dt );
    void RotX ( float dt );
    const QMatrix4x4 & getMatrix();

public slots:
    void setViewAngle ( int  va );

private:
    int       viewAngle;
    float     roty;
    float     rotx;
    QVector3D pos;
    QMatrix4x4 mat;
    QMatrix4x4 mat0;
};

#endif // CAMERA_H
