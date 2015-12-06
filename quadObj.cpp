
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
#include "emptyobj.h"
#include "glwidget.h"           // TODO
#include "mainwindow.h"         // TODO

#include "quadObj.h"


#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_TEXCOORD_ATTRIBUTE 1

QuadObj::QuadObj(const QString name, ObjectItem *parent, Project &pro1) :
    pro ( pro1 ) ,  EmptyObj ( name , parent)
{
    rotation.setToIdentity();
    pos   = QVector3D ( -2, -1,-3 );
    rot   = QVector3D ( 0, 0, 0 );
    scale = QVector3D ( 1, 1, 1 );
    makeobject();
    textureID = 0;
    textureMat = new cv::Mat (cv::Size(500,500),CV_8UC3);
}

QuadObj::~QuadObj() {
    //qDebug() << "delet QuadObj";
    delete textureMat;
}

std::string  QuadObj::getType() const {
    return std::string("QUAD");
}


/*
 * Make this object
 * ************************************************/
void QuadObj::makeobject () {
    vertices.append ( QVector3D ( -0.5f , 0.5f , 0 ));        // Make face
    vertices.append ( QVector3D ( -0.5f ,-0.5f , 0 ));
    vertices.append ( QVector3D (  0.5f ,-0.5f , 0 ));
    vertices.append ( QVector3D (  0.5f , 0.5f , 0 ));

    texCoords.append( QVector2D ( 0,0));                      // Set Texture coordinate
    texCoords.append( QVector2D ( 0,1));
    texCoords.append( QVector2D ( 1,1));
    texCoords.append( QVector2D ( 1,0));
}

/*
 *
 * **************************************************/
void QuadObj::takeTexture() {
    // Calculate Matrix using the parent matrixes too
    std::stack<QMatrix4x4> mats;
    QMatrix4x4 cmat;

    // Store previous matrixes in stack
    QuadObj *po = this;
    bool notroot = true;
    while ( notroot ) {

        if ( po != manager->mainproject->objectRoot ) {
            mats.push( po->getMatrix() );
           // qDebug() << po->m_itemData;
            po = (QuadObj * ) po->parentItem();
        } else {
            mats.push( po->getMatrix() );
            //qDebug() << po->m_itemData;
            notroot = false;
        }
    }

    cmat = manager->fixCamera->getMatrix();
    for ( int i=0 , e = mats.size(); i < e ; i ++ ) {
        cmat *= mats.top();
        mats.pop();
       // qDebug() << "mat";
    }
    cmat.scale(scale);

    QVector3D vect;
    qDebug() << "verticies " << vertices.size();
    qDebug() << "TexCoords " << texCoords.size();
    for ( int i = 0; i < vertices.size(); i++) {    // verticies.size
        vect =  cmat * vertices[i];
        texCoords[i] = QVector2D ( ( vect.x()   + 1 ) / 2   ,
                                   ( 1 - vect.y() )  / 2 );
    }

    // The output texture image coordinate and size
    int w,h;
    w = textureMat->cols;
    h = textureMat->rows;

    cv::Point2f ocoords[4];
    ocoords[0] = cv::Point2f (0, 0);
    ocoords[1] = cv::Point2f (0, h);
    ocoords[2] = cv::Point2f (w, h);
    ocoords[3] = cv::Point2f (w, 0);
    //
    cv::Point2f textpoint[4];
    UvtoCvCoordinate(manager->mainproject->actualBackground, textpoint);

  /*  for ( int i = 0; i < 4; i++) {
        qDebug() << textpoint[i].x << " : " << textpoint[i].y;
        cv::circle( manager->mainproject->actualBackground, textpoint[i],5, cv::Scalar(1,255,1), 3 );
    }*/

 //   sortCorners(textpoint);
  //  manager->mainwindow->glWidget->UploadTexture(manager->mainproject->actualBackground.cols ,
   //               manager->mainproject->actualBackground.rows,
    //             manager->mainproject->actualBackground.data );


    cv::Mat ptransform = getPerspectiveTransform ( textpoint, ocoords);
  //  cv::Mat transmtx = cv::getPerspectiveTransform(corners, quad_pts);
    cv::warpPerspective( *manager->mainproject->actualBackground, *textureMat, ptransform,  textureMat->size() );

    GLWidget & gl = manager->getMainGLW();
    if ( textureID == 0 ) {
        gl.glGenBuffers( 1, &textureID);
    }
    gl.glBindTexture ( GL_TEXTURE_2D , textureID);
    gl.glTexImage2D(  GL_TEXTURE_2D, 0, GL_RGB, textureMat->cols, textureMat->rows, 0, GL_RGB,
                      GL_UNSIGNED_BYTE, ( GLvoid * ) textureMat->data );
    gl.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    gl.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    gl.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gl.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //qDebug() << "Background ID:" << manager->mainproject->backtextID;
    qDebug() << "TextureId:" << textureID;
    //texCoords.clear();
    texCoords[0] =  QVector2D ( 0,0);                      // Set Texture coordinate
    texCoords[1] =  QVector2D ( 0,1);
    texCoords[2] =  QVector2D ( 1,1);
    texCoords[3] =  QVector2D ( 1,0);
    textPixmap   =  QPixmap::fromImage( this->cvMatToQImage( *textureMat) );


}

/*
 * Draw QuadObj on given gl context, with
 * given camera ( projection and view matrix ).
 * We have to translate and rotate our QuadObj.
 * ************************************************/
void QuadObj::drawgl(GLWidget &gl, QMatrix4x4 & cameramat  ) {

    QMatrix4x4 mobj = cameramat;

    mobj *= this->getMatrix();
    mobj.scale(scale);

    static  QColor color ( 1.0f, 0, 0.5f, 1 );

    QGLShaderProgram * sp = gl.program;

    if ( manager->mainproject->actualobject == this ) {
        sp = gl.program2;
    }

    sp->enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
    sp->enableAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE);
    sp->setAttributeArray   (PROGRAM_VERTEX_ATTRIBUTE, vertices.constData());
    sp->setAttributeArray   (PROGRAM_TEXCOORD_ATTRIBUTE, texCoords.constData());
    sp->bind();
    sp->setUniformValue("matrix", mobj);
    sp->setUniformValue("color", QVector4D (0,0,1,0.5f));

    gl.glBindTexture(GL_TEXTURE_2D, this->textureID );
    gl.glDrawArrays(GL_QUADS, 0, 4 );

    if ( manager->edges ) {
        gl.glDisable(GL_CULL_FACE);
        sp = gl.solidcolorp;

        sp->enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
        sp->enableAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE);
        sp->setAttributeArray   (PROGRAM_VERTEX_ATTRIBUTE, vertices.constData());
        sp->setAttributeArray   (PROGRAM_TEXCOORD_ATTRIBUTE, texCoords.constData());
        sp->bind();
        sp->setUniformValue("matrix", mobj);
        sp->setUniformValue("color", QVector4D (0,1,0,0.8f));

        if ( manager->mainproject->actualobject == this ) {
            sp->setUniformValue("color", QVector4D (1,0.8f,1,0.8f));
        }
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        gl.glLineWidth(2);
        gl.glDrawArrays(GL_QUADS, 0, 4 );
        gl.glEnable(GL_CULL_FACE);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

}

/* Load Quad from file
 *
 * **********************************************************/
bool QuadObj::loadFromFile(std::ifstream & inputstream) {
    std::string str;
    float x,y,z;
    char v;
    // read position
    std::getline(inputstream, str );
    std::stringstream ss(str);
    ss >> x;    ss >> v;    ss >> y;    ss >> v;    ss >> z;
    qDebug() << x << "," << y << ";" << z;
    pos = QVector3D(x,y,z);
    // read rotmatrix
    for ( int i=0; i < 3; i++) {
        std::getline(inputstream, str );
        std::stringstream ss(str);
        ss >> x;    ss >> v;    ss >> y;    ss >> v;    ss >> z;
        this->rotation.setColumn(i,QVector3D (x,y,z));
    }
    // read scale
    std::getline(inputstream, str );
    std::stringstream ss1(str);
    ss1 >> x;    ss1 >> v;    ss1 >> y;    ss1 >> v;    ss1 >> z;
    scale = QVector3D (x,y,z);
    // read verticies
    vertices.clear();
    for ( int i=0; i < 4; i++) {
        std::getline(inputstream, str );
        std::stringstream ss(str);
        ss >> x;    ss >> v;    ss >> y;    ss >> v;    ss >> z;
        vertices.append(QVector3D (x,y,z));
    }


    return true;
}

/* Save Quad to file
 *
 * **************************************************************/
bool QuadObj::saveToFile(std::ofstream & outstream) {
    outstream << m_itemData.toStdString() << std::endl;
    outstream << pos.x() << ",";
    outstream << pos.y() << ",";
    outstream << pos.z() << std::endl;


    for ( int i=0; i  <3 ; i++ ) {
        outstream << rotation.column(i).x() << ",";
        outstream << rotation.column(i).y() << ",";
        outstream << rotation.column(i).z() ;
        outstream << std::endl;
    }
    outstream << scale.x() << "," << scale.y() << "," << scale.z() << std::endl;

    for ( int i=0; i  <4 ; i++ ) {
        outstream << this->vertices[i].x() << ",";
        outstream << this->vertices[i].y() << ",";
        outstream << this->vertices[i].z() ;
        outstream << std::endl;
    }
    return true;
}


