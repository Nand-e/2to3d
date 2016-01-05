
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


#include "CubeObj.h"
#include "emptyobj.h"
//#include "Globals.h"
#include "project.h"
#include "manager.h"

#include <qglshaderprogram.h>
#include <QMatrix4x4>


#include <stack>


#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_TEXCOORD_ATTRIBUTE 1
/*
CubeObj::CubeObj() :
    EmptyObj ( QString("Null"), 0 )
{

}*/


CubeObj::CubeObj(const QString name, ObjectItem *parent, Project & pro1 )
    : pro ( pro1 ), EmptyObj ( name, parent )
{
    makeobject();
    textureID = 0;
    textureMat = new cv::Mat (cv::Size(500,500),CV_8UC3);
    for ( int i=0; i < 6; i++)  textureIDs[i] = 0;
}

CubeObj::~CubeObj () {
    delete  textureMat;
}

std::string CubeObj::getType() const {
   return std::string("CUBE");
}


void CubeObj::makeobject () {
    vertices.append ( QVector3D ( -0.5f , 0.5f , 0.5f ));        // Make face Front
    vertices.append ( QVector3D ( -0.5f ,-0.5f , 0.5f ));
    vertices.append ( QVector3D (  0.5f ,-0.5f , 0.5f ));
    vertices.append ( QVector3D (  0.5f , 0.5f , 0.5f ));

    vertices.append ( QVector3D (  0.5f , 0.5f ,  0.5f ));        // Make face Right side
    vertices.append ( QVector3D (  0.5f ,-0.5f ,  0.5f ));
    vertices.append ( QVector3D (  0.5f ,-0.5f , -0.5f ));
    vertices.append ( QVector3D (  0.5f , 0.5f , -0.5f ));

    vertices.append ( QVector3D ( -0.5f , 0.5f , 0.5f ));        // Make face Left side
    vertices.append ( QVector3D ( -0.5f , 0.5f , -0.5f ));
    vertices.append ( QVector3D ( -0.5f , -0.5f , -0.5f ));
    vertices.append ( QVector3D ( -0.5f , -0.5f , 0.5f ));

    vertices.append ( QVector3D ( -0.5f , 0.5f , -0.5f ));        // Make face up
    vertices.append ( QVector3D ( -0.5f , 0.5f ,  0.5f ));
    vertices.append ( QVector3D (  0.5f , 0.5f , 0.5f ));
    vertices.append ( QVector3D (  0.5f , 0.5f , -0.5f ));

    vertices.append ( QVector3D ( -0.5f , -0.5f , -0.5f ));        // Make face down
    vertices.append ( QVector3D ( -0.5f , -0.5f ,  0.5f ));
    vertices.append ( QVector3D (  0.5f , -0.5f , 0.5f ));
    vertices.append ( QVector3D (  0.5f , -0.5f , -0.5f ));

    vertices.append ( QVector3D ( -0.5f , 0.5f , -0.5f ));        // Make face Back
    vertices.append ( QVector3D (  0.5f , 0.5f , -0.5f ));
    vertices.append ( QVector3D (  0.5f , -0.5f , -0.5f ));
    vertices.append ( QVector3D (  -0.5f , -0.5f , -0.5f ));

    texCoords.clear();
    texCoords.append( QVector2D ( 0,0));                          // Set Texture coordinate
    texCoords.append( QVector2D ( 0,1));
    texCoords.append( QVector2D ( 1,1));
    texCoords.append( QVector2D ( 1,0));
    // Set Texture coordinate
    texCoords.append( QVector2D ( 0,0));
    texCoords.append( QVector2D ( 0,1));
    texCoords.append( QVector2D ( 1,1));
    texCoords.append( QVector2D ( 1,0));
    // Set Texture coordinate
    texCoords.append( QVector2D ( 0,0));
    texCoords.append( QVector2D ( 0,1));
    texCoords.append( QVector2D ( 1,1));
    texCoords.append( QVector2D ( 1,0));

    // Set Texture coordinate
    texCoords.append( QVector2D ( 0,0));
    texCoords.append( QVector2D ( 0,1));
    texCoords.append( QVector2D ( 1,1));
    texCoords.append( QVector2D ( 1,0));
    // Set Texture coordinate
    texCoords.append( QVector2D ( 0,0));
    texCoords.append( QVector2D ( 0,1));
    texCoords.append( QVector2D ( 1,1));
    texCoords.append( QVector2D ( 1,0));

    // Set Texture coordinate
    texCoords.append( QVector2D ( 0,0));
    texCoords.append( QVector2D ( 0,1));
    texCoords.append( QVector2D ( 1,1));
    texCoords.append( QVector2D ( 1,0));
}

void CubeObj::UvtoCvCoordinate (cv::Mat & input, QVector<QVector2D> & inPoints, cv::Point2f * output  ) {
    unsigned int w,h;
    w = input.cols;
    h = input.rows;
    for ( int i = 0; i < inPoints.size() ; i ++ ) {
        output[i] = cv::Point2f( inPoints.at(i).x()  *w, inPoints.at(i).y() * h );
    }
}




/*
 *
 * **************************************************/
void CubeObj::takeTexture() {
    // Calculate Matrix using the parent matrixes too
    std::stack<QMatrix4x4> mats;
    QMatrix4x4 cmat;

    // Store previous matrixes in stack
    CubeObj *po = this;
    bool notroot = true;
    while ( notroot ) {
        if ( po != pro.objectRoot ) {
            mats.push( po->getMatrix() );
           // qDebug() << po->m_itemData;
            po = (CubeObj * ) po->parentItem();
        } else {
            mats.push( po->getMatrix() );
            //qDebug() << po->m_itemData;
            notroot = false;
        }
    }

    // camera mat * parent mat * parent mat ..... * parent mat * this mat * this scale
//    cmat = pro.getManger().fixCamera->getMatrix();          // TODO
    for ( int i=0 , e = mats.size(); i < e ; i ++ ) {
        cmat *= mats.top();
        mats.pop();
       // qDebug() << "mat";
    }
    cmat.scale(scale);

    // Project points to screen
    QVector3D vect;
    qDebug() << "verticies " << vertices.size();
    qDebug() << "TexCoords " << texCoords.size();

    QVector<QVector2D> projectedPoints;
    for ( int i = 0; i < vertices.size(); i++) {    // verticies.size
        vect =  cmat * vertices[i];
        projectedPoints.append(  QVector2D ( ( vect.x()   + 1 ) / 2   , ( 1 - vect.y() )  / 2 ) );
    }

    // The output texture image coordinate and size
    int w,h;
    w = textureMat->cols;
    h = textureMat->rows;

    cv::Point2f ocoords[ 4 ];
    ocoords[0] = cv::Point2f (0, 0);
    ocoords[1] = cv::Point2f (0, h);
    ocoords[2] = cv::Point2f (w, h);
    ocoords[3] = cv::Point2f (w, 0);

    cv::Point2f textpoints[24];      // TODO
 //   UvtoCvCoordinate( *pro.actualBackground, projectedPoints, textpoints ); TODO
/*
    // for test
    for ( int i = 0; i < 24 ; i++) {
        //qDebug() << textpoints[i].x << " : " << textpoints[i].y;
        cv::circle( pro.actualBackground, textpoints[i],3, cv::Scalar(1,255,1), 2 );
        pro.reLoadback();
    }
    // -------------------*/

    GLWidget & gl = pro.getManger().getMainGLW();
    for ( int i =0; i < 6; i++) {
        cv::Mat ptransform = getPerspectiveTransform ( &textpoints[i*4], ocoords);
//        cv::warpPerspective( *pro.actualBackground, *textureMat, ptransform,  textureMat->size() );
        if ( textureIDs[i] == 0 ) {
            gl.glGenBuffers( 1, &textureIDs[i]);
            qDebug() << "TextureId:" << textureIDs[i];
        }
        gl.glBindTexture ( GL_TEXTURE_2D , textureIDs[i]);
        gl.glTexImage2D(  GL_TEXTURE_2D, 0, GL_RGB, textureMat->cols, textureMat->rows, 0, GL_RGB,
                          GL_UNSIGNED_BYTE, ( GLvoid * ) textureMat->data );
        gl.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        gl.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        gl.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        gl.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    }



  /*  texCoords[0] =  QVector2D ( 0,0);                      // Set Texture coordinate
    texCoords[1] =  QVector2D ( 0,1);
    texCoords[2] =  QVector2D ( 1,1);
    texCoords[3] =  QVector2D ( 1,0);*/
 /*  textPixmap   =  QPixmap::fromImage( this->cvMatToQImage( *textureMat) );*/


}



/*
 *
 *
 * **************************************************************/
bool CubeObj::saveToFile(std::ofstream & outstream) {
    outstream << m_itemData.toStdString() << std::endl;
    outstream << pos.x() << "," << pos.y() << "," << pos.z() << std::endl;

    for ( int i=0; i  <3 ; i++ ) {
        outstream << rotation.column(i).x() << ",";
        outstream << rotation.column(i).y() << ",";
        outstream << rotation.column(i).z() ;
        outstream << std::endl;
    }
    outstream << scale.x() << "," << scale.y() << "," << scale.z() << std::endl;

  /*  for ( int i=0; i  < 24 ; i++ ) {
        outstream << this->vertices[i].x() << ",";
        outstream << this->vertices[i].y() << ",";
        outstream << this->vertices[i].z() ;
        outstream << std::endl;
    }*/
    return true;
}

/*
 *
 * *************************************************************/
bool CubeObj::loadFromFile(std::ifstream & inputstream) {
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
    //   vertices.clear();
/*    for ( int i=0; i < 24; i++) {
        std::getline(inputstream, str );
        std::stringstream ss(str);
        ss >> x;    ss >> v;    ss >> y;    ss >> v;    ss >> z;
        vertices.append(QVector3D (x,y,z));
    }*/
    return true;
}

void CubeObj::drawgl(GLWidget &gl, QMatrix4x4 & cameramat  ) {

    QMatrix4x4 mobj = cameramat;

    mobj *= getMatrix();
    mobj.scale(scale);

    static  QColor color ( 1.0f, 0, 0.5f, 1 );

    QGLShaderProgram * sp = gl.program;

    if ( pro.actualobject == this ) {
        sp = gl.program2;
    }

    for ( int i=0; i <6; i++) {

        sp->enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
        sp->enableAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE);
        sp->setAttributeArray   (PROGRAM_VERTEX_ATTRIBUTE, vertices.constData());
        sp->setAttributeArray   (PROGRAM_TEXCOORD_ATTRIBUTE, texCoords.constData());
        sp->bind();
        sp->setUniformValue("matrix", mobj);
        sp->setUniformValue("color", QVector4D (1,0,0,0.2f));
        gl.glBindTexture(GL_TEXTURE_2D, this->textureIDs[i] );
        gl.glDrawArrays(GL_QUADS, i*4, 4 );
    }


    if ( pro.getManger().edges ) {
        gl.glDisable(GL_CULL_FACE);
        sp = gl.solidcolorp;

        sp->enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
        sp->enableAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE);
        sp->setAttributeArray   (PROGRAM_VERTEX_ATTRIBUTE, vertices.constData());
        sp->setAttributeArray   (PROGRAM_TEXCOORD_ATTRIBUTE, texCoords.constData());
        sp->bind();
        sp->setUniformValue("matrix", mobj);
        sp->setUniformValue("color", QVector4D (0,1,0,0.8f));

        if ( pro.actualobject == this ) {
            sp->setUniformValue("color", QVector4D (1,0.8f,1,0.8f));
        }
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        gl.glLineWidth(2);
        gl.glDrawArrays(GL_QUADS, 0, 24 );
        gl.glEnable(GL_CULL_FACE);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

}


