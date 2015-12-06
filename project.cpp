
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <string>
#include <fstream>

#include <QDebug>
#include <QGLShaderProgram>

#include "project.h"
#include "Globals.h"
#include "mainwindow.h"
#include "treemodel.h"
#include "itemform.h"
#include "projecttreeview.h"
#include "manager.h"


#include "imageitem.h"
#include "cubeObj.h"
#include "quadObj.h"

#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_TEXCOORD_ATTRIBUTE 1


Project::Project(Manager & m) : man (m)
{   
    renderEnable = false;
    container =  new TreeModel( 0 , this );         // Store the objct3d object and the other project specifc data
    createRoots();

    imagesRoot->appendChild(new ImageItem ("Image-1" , "grid.png", imagesRoot ));
    dynamic_cast<ImageItem*> ( imagesRoot->child(0) ) -> initPicture ();

    actualBackground =     & ( dynamic_cast<ImageItem*> ( imagesRoot->child(0) ) ->picture ) ;

    actualobject = 0;
    backtextID = 0;

    ObjectItem * op;
    for ( int i =0; i < 3; i++ ) {
        op = new QuadObj (QString("object") + QString::number(i) ,  objectRoot , * this  );
        op->step(QVector3D ( i * 1.25f, 0 , 0 ));
        objectRoot->appendChild( op);
    }

    for ( int i =0; i < 8; i++ ) {
        op = new CubeObj (QString("object2") + QString::number(i+1) , objectRoot->child(2), *this);
        op->step(QVector3D ( 1 + i * 1.25f , 0 , -2 ));
        objectRoot->child(2)->appendChild(op);
    }


    for ( int i =0; i < 5; i++ ) {
        op = new QuadObj (QString("object2") + QString::number(i+1) , objectRoot->child(2), *this);
        op->step(QVector3D ( 4 + i * 1.25f , 0 , -2 ));
        objectRoot->child(2)->appendChild(op);
    }



    man.ptreeview->setModel( container );

}

Project::~Project()
{
    delete container;

}

Manager & Project::getManger() {
    return man;
}

/*
 *
 * * ************************************/
void Project::createRoots() {

    imagesRoot = new ImageItem ( "Pictures", "Root", container->getRoot() );
    container->getRoot()->appendChild( imagesRoot );  

    container->getRoot()->appendChild( new QuadObj ( "Objects", container->getRoot() , * this  ));

    actualobject = (QuadObj *) container->getRoot()->child(1);
    objectRoot   = (QuadObj *) container->getRoot()->child(1);

}

void Project::treeCliked(QModelIndex index){
    //qDebug() << index;
    actualobject = ( ObjectItem*) (index.internalPointer() );
    man.mainwindow->itemform->updateData( );
    man.keycontrol = Manager::ItemControl;
    //qDebug() << actualobject;
}
void Project::initGlpart(GLWidget &gl )
{
    loadBackground( gl , imagename );

    faceVertex.append ( QVector3D ( -1 , 1 , 0 ));        // Make face
    faceVertex.append ( QVector3D ( -1 ,-1 , 0 ));
    faceVertex.append ( QVector3D (  1 ,-1 , 0 ));
    faceVertex.append ( QVector3D (  1 , 1 , 0 ));

    faceTex.append ( QVector2D ( 0,0) );                  // Set Texture coordinate
    faceTex.append ( QVector2D ( 0,1) );
    faceTex.append ( QVector2D ( 1,1) );
    faceTex.append ( QVector2D ( 1,0) );
    renderEnable = true;
}

/*
 *
 *
 * **********************************************/
void Project::drawBackground (GLWidget &gl)
{

    if ( man.actualCamera == man.freeCamera) return;

    QMatrix4x4 m;
    m.ortho( -1,1, -1, 1, -100, 500 );
    m.translate(0,0,-499);
    m.scale( 1, 1, 1 );
    QColor color (0,1,1,0.5f);
    gl.program->enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
    gl.program->enableAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE);
    gl.program->setAttributeArray(PROGRAM_VERTEX_ATTRIBUTE, faceVertex.constData());
    gl.program->setAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE, faceTex.constData());
    gl.program->bind();

    gl.program->setUniformValue("matrix", m);
    gl.program->setUniformValue("color", color );

    gl.glBindTexture(GL_TEXTURE_2D, backtextID );
    gl.glDrawArrays(GL_QUADS, 0 , 4);


}

void Project::drawObjects(GLWidget &glw)
{
    if ( !renderEnable) return;
    QMatrix4x4 mat = man.actualCamera->getMatrix();
    mat *= objectRoot->getMatrix();
    drawHelper( objectRoot , glw, mat );
}

void Project::drawHelper (ObjectItem *obj, GLWidget &glw, QMatrix4x4 camp) {

    for ( int i =0; i < obj->childCount(); i ++) {
        obj->child(i)->drawgl( glw, camp);
        QMatrix4x4 mat = camp * obj->child(i)->getMatrix();
        drawHelper(obj->child(i), glw, mat );
    }
}

bool Project::keyEvent(QKeyEvent *event){
    if ( actualobject != 0 ) {
         bool proc = actualobject->manipulate( event );
         man.mainwindow->itemform->updateData( );
         return proc;
    }
    return false;
}


bool Project::reLoadback () {

    GLWidget & gl = man.getMainGLW();

    if ( backtextID  == 0 ) {
        gl.glGenBuffers( 1, &backtextID );
        qDebug() << "Genereste Texture for BAckground, id:" << backtextID;
    }
    unsigned int w = actualBackground->cols;
    unsigned int h = actualBackground->rows;

    gl.glBindTexture ( GL_TEXTURE_2D , backtextID);
    gl.glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB,
                   GL_UNSIGNED_BYTE, ( GLvoid * ) actualBackground->data );

    gl.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    gl.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    gl.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gl.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    return true;
}

bool Project::loadBackground( GLWidget & gl, QString name) {

   /* actualBackground = cv::imread( imagename.toStdString() );
    if(! actualBackground->data ) {
        qDebug() <<  "Could not open or find the image: " << imagename;
        return false;
    }
    else {
        cv::cvtColor( *actualBackground, *actualBackground,   CV_BGR2RGB);
        int w,h;
        w = actualBackground->cols;
        h = actualBackground->rows;
        if ( backtextID  == 0 ) {
            gl.glGenBuffers( 1, &backtextID );
        }
        gl.glBindTexture ( GL_TEXTURE_2D , backtextID);
        gl.glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB,
                       GL_UNSIGNED_BYTE, ( GLvoid * ) actualBackground->data );
        qDebug() << "Genereste Texture for BAckground, id:" << backtextID;
        gl.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        gl.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        gl.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        gl.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        return true;
    }*/
    return true;
}






void Project::clearProject() {
    renderEnable = false;
    container->clearAlldata();
    createRoots();
    renderEnable = true;
   // qDebug() << "Render Ennbled";
}

/*
 * **************************************************/
bool Project::loadFile () {
    qDebug() << "Load File";
    std::ifstream is("valami.txt");
    std::string line;
    if ( !is.is_open()) {
        qDebug() << " File not openned!!!";
        return false;
    }
    else {
        this->clearProject();       // clear actual project ( TO DO )
        bool end = false;
        int  parentID;
        int  ID;
        std::map<int, ObjectItem * > objectmap;
        for ( int i=0; i < 14; i++ ) {
            getline ( is, line);
        }
        // read image name
        getline ( is, line );
        imagename = QString ( line.c_str() );
        // read camera view angle
        getline ( is, line );
        int viewangle = std::atoi( line.c_str() );
        man.fixCamera->setViewAngle(viewangle);
        man.freeCamera->setViewAngle(viewangle);
        std::string otype;
        while ( !is.eof())
        {
            // Object factoring magic
            getline ( is, otype );
            getline ( is, line);
            parentID = atoi ( line.c_str());

            end  = getline ( is, line);
            ID = atoi ( line.c_str() );
            end  = getline ( is, line);
            qDebug() << QString (line.c_str());
            if ( is.eof()) break;
            ObjectItem * op;
            ObjectItem * oparent;

            if ( parentID != 0 ){
                oparent = objectmap.at(parentID); // TODO need try catch
            } else {
                oparent = objectRoot;
            }

            if ( otype.compare("QUAD") == 0 ) {
                op =  new QuadObj ( QString (line.c_str() ), oparent, * this );
            }
            else  if ( otype.compare("CUBE") == 0 ) {
                op =  new CubeObj ( QString (line.c_str() ), oparent, * this );
            } else {
                op =  new QuadObj ( QString (line.c_str() ), oparent, * this );
            }

            objectmap[ID] = op;
            oparent->appendChild( op );
            op->loadFromFile( is );
            getline ( is, line);
        }
    }
    is.close();
    this->loadBackground(man.getMainGLW(), imagename);
    container->updateModel();
    return true;
}


/*
 * Save whole project to file (txt version)
 *
 *
 * ************************************************************************/
bool Project::saveToFile () {
    int objID = 0;
    int level = 0;
    std::ofstream outstream("valami.txt");
    if ( !outstream.is_open() )
    {
        qDebug() << "File not openned!";
        return false;
    }

    for ( int i= 0; i < 14; i++ ) {
        outstream << i << std::endl;
    }
    outstream << this->imagename.toStdString() << std::endl;
    outstream << (int) man.fixCamera->getViewAngle() << std::endl;
    saveChildren ( objID, level, objectRoot, outstream );
    outstream.close();
    return true;
}

/*
 * Save QuadObj from Treemodell container
 *
 * ******************************************************/
bool  Project::saveChildren (int parentid, int & level, ObjectItem *obj,  std::ofstream & outstream ) {

    level ++;
    //int idstep = std::pow (( double ) 10 , level);
    int id = parentid * 100;

    for ( int i = 0 ; i < obj->childCount(); i++ ) {
        id ++;
        ObjectItem * obj1 =   obj->child(i) ;
        outstream << obj1->getType() << std::endl;
        outstream << parentid << std::endl;
        outstream << id << std::endl;
        obj1->saveToFile( outstream);
        outstream << "###### check this line!" << std::endl;
        if ( obj1->childCount() > 0 ) {
            saveChildren ( id, level, obj1, outstream );
        }
    }
    level --;
    return true;
}

