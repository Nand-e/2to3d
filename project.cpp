
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

#include "obj3dfactory.h"
#include "imageitem.h"
#include "cubeObj.h"
#include "quadObj.h"

#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_TEXCOORD_ATTRIBUTE 1


Project::Project(Manager & m) :
    man (m),
    container ( new TreeModel( 0 , this ) )          // store Items such as pictures, 3d objects etc
{   
    renderEnable = false;

    createRoots();

    man.actualCamera  =  dynamic_cast<ImageItem*> ( imagesRoot )->getCamera();

    actualobject = 0;
    actualImage  = dynamic_cast<ImageItem * > (imagesRoot);


    ObjectItem * op;
    for ( int i =0; i < 3; i++ ) {
        op = new QuadObj (QString("object") + QString::number(i) ,  objectRoot , * this  );
        op->step(QVector3D ( i * 1.25f, 0 , 0 ));
        objectRoot->appendChild( op);
    }

    for ( int i =0; i < 3; i++ ) {
        op = new CubeObj (QString("object2") + QString::number(i+1) , objectRoot->child(2), *this);
        op->step(QVector3D ( 1 + i * 1.25f , 0 , -2 ));
        objectRoot->child(2)->appendChild(op);
    }


    for ( int i =0; i < 3; i++ ) {
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

void Project::aspectChanged( float aspect) {
   viewportAspect = aspect;
   qDebug()<< "AspectRatio:" << viewportAspect;
}

/*
 *
 * * ************************************/
void Project::createRoots() {

    imagesRoot = new ImageItem ( "Pictures", "grid.png", container->getRoot(), *this );
    container->getRoot()->appendChild( imagesRoot );  
    container->getRoot()->appendChild( new CubeObj ( "Objects", container->getRoot() , * this  ));
    actualobject = (QuadObj *) container->getRoot()->child(1);
    objectRoot   = (QuadObj *) container->getRoot()->child(1);

}

void Project::addImage( ) {

    QString fileName = QFileDialog::getOpenFileName(0 , tr("Open Image"), "Image", tr("Image (*.jpg)"));

    ObjectItem * image = Obj3dFactory::createObj3d( QString ("IMAGE"), imagesRoot, fileName, fileName);
    if ( static_cast<ImageItem * > (image)->initPicture() == true  ) {
         container->addObject( image );

    } else {
         delete image;
    }

}

void Project::addObject(ObjectItem *newItem ) {
    container->addObject ( newItem  );
}

/*
 * Delete object from data modell
 * ********************************************************************/
void Project::deleteObject(ObjectItem *item) {
    if ( item == objectRoot || item == imagesRoot ) {
        qDebug() << "you are not allowd to delete root items!";
        return;
    }

    if ( item->getType().compare("IMAGE") == 0) {          // Ha a t0relnendő elem kép
        if ( actualImage == item ) actualImage = 0;
    } else {
        if ( item == actualobject ) actualobject = 0;
    }
    container->deleteObject( item );
}



void Project::treeCliked(QModelIndex index){
    //qDebug() << index;

    ObjectItem * p = ( ObjectItem*) (index.internalPointer() );
    qDebug() << p->getType().c_str();
    if ( p->getType().compare("IMAGE") == 0 )
    {
      actualImage  =  static_cast<ImageItem*> ( p );

    } else {
        actualobject = p;
        man.mainwindow->itemform->updateData( );
        man.keycontrol = Manager::ItemControl;
    }
    //qDebug() << actualobject;
}
void Project::initGlpart(GLWidget &gl )
{
    dynamic_cast<ImageItem*> ( imagesRoot ) ->initPicture();
    //dynamic_cast<ImageItem*> ( imagesRoot->child(0) ) -> initPicture ();

    renderEnable = true;
}

/*
 * **********************************************/
void Project::drawBackground (GLWidget &gl)
{

    if ( man.actualCamera == man.freeCamera) return;
    if ( actualImage == 0 ) return;
    QMatrix4x4 m;
    m.ortho( - 1 * viewportAspect , 1 * viewportAspect , -1, 1, -100, 500 );
    m.translate(0,0,-499);
    m.scale( 1.0f , 1.0f , 1 );
    QColor color (0,1,1,0.5f);

    gl.program->enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
    gl.program->enableAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE);
    gl.program->setAttributeArray(PROGRAM_VERTEX_ATTRIBUTE  , actualImage->faceVertex.constData());
    gl.program->setAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE, actualImage->faceTex.constData());
    gl.program->bind();

    gl.program->setUniformValue("matrix", m);
    gl.program->setUniformValue("color", color );

    gl.glBindTexture(GL_TEXTURE_2D, actualImage->glID);
    gl.glDrawArrays(GL_QUADS, 0 , 4);

    QGLShaderProgram * sp = gl.program;

    gl.glDisable(GL_CULL_FACE);
    sp = gl.solidcolorp;
    m.translate(0,0,50);
    m.scale( 0.98f , 0.98f , 1 );

    sp->enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
    sp->enableAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE);
    sp->setAttributeArray   (PROGRAM_VERTEX_ATTRIBUTE  , actualImage->faceVertex.constData());
    sp->setAttributeArray   (PROGRAM_TEXCOORD_ATTRIBUTE, actualImage->faceTex .constData());
    sp->bind();
    sp->setUniformValue("matrix", m);
    sp->setUniformValue("color", QVector4D (0,0,1,0.8f));

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    gl.glLineWidth(1);
    gl.glDrawArrays(GL_QUADS, 0, 4 );

    gl.glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);



}

void Project::mousePressEvent(QMouseEvent *event) {
    lastPos = event->pos();
}

void Project::mouseEvent ( QMouseEvent * event ) {
    float dx = ( float ) ( event->x() - lastPos.x() )/ 5;
    float dy = ( float ) ( event->y() - lastPos.y() )/ 5;

    Camera * cam;
    if ( freecam) {
        cam = man.freeCamera;
    } else {
        if ( actualImage != 0 ) {
            cam = actualImage->getCamera();
        } else {
            return;
        }
    }


    if (event->buttons() & Qt::RightButton) {
        cam->RotY ( dx );
        cam->RotX ( dy );

    } else if (event->buttons() & Qt::LeftButton) {
        cam->UpDown( dy / 10  );
        cam->LeftRight( dx /10 );
    }
    lastPos = event->pos();
}

void Project::drawObjects(GLWidget &glw)
{
    if ( !renderEnable) return;

    QMatrix4x4 mat;
    if ( this->freecam ) {
        mat = man.freeCamera->getMatrix( viewportAspect );

    } else {
        if ( actualImage == 0) {
            mat.perspective(60, viewportAspect, 1, 500);
        } else {
            mat = actualImage->getCamera()->getMatrix( viewportAspect );
        }
    }
    //mat *= objectRoot->getMatrix();
    drawHelper( objectRoot , glw, mat );
}

void Project::drawHelper (ObjectItem *obj, GLWidget &glw, QMatrix4x4 camp) {

    for ( int i =0; i < obj->childCount(); i ++) {
        obj->child(i)->drawgl( glw, camp);
        QMatrix4x4 mat = camp * obj->child(i)->getMatrix();
        drawHelper(obj->child(i), glw, mat );
    }
}

/*
 *
 * *******************************************************/
bool Project::keyEvent(QKeyEvent *event){
    if ( actualobject != 0 ) {
         bool proc = actualobject->manipulate( event );
         man.mainwindow->itemform->updateData( );
         return proc;
    }
    return false;
}

/*
 *
 * *******************************************************/
bool Project::eventFilter(QObject* object,QEvent* event) {

    bool processed = false;
    if(event->type() == QEvent::KeyPress) {
        if ( man.keycontrol == Manager::ItemControl ) {
             processed = keyEvent( ( QKeyEvent * ) event);
        } else {
            if ( freecam ) {
                processed = man.freeCamera->keyEvent(( QKeyEvent * ) event );
            } else {
                if ( actualImage != 0) {
                    processed = actualImage->getCamera()->keyEvent( ( QKeyEvent * ) event  );
                }
            }
        }
        if ( processed ) { return true; }
    }
    return QObject::eventFilter(object,event);
}


void Project::setViewAngle( int va ) {
    if ( actualImage != 0 ) {
        actualImage->getCamera()->setViewAngle(va);
    }
}




void Project::clearProject() {
    renderEnable = false;
    actualImage  = 0;
    actualobject = 0;

    container->clearAlldata( objectRoot );
    // createRoots();
    renderEnable = true;
    // qDebug() << "Render Ennbled";
}

#define ENDFIRSTPART "#FEND"

/*
 * **************************************************/
bool Project::loadFile ( QString & filename) {
    qDebug() << "Load File";
    std::ifstream is(filename.toStdString());
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
        for ( int i=0; i < 10; i++ ) {
            getline ( is, line);
        }

        // ----------- Images --------------------------------------------
        ObjectItem * pimage;
        unsigned int i = 0;
        do {
            getline ( is, line );
            qDebug () << line.c_str();
            if ( line.compare (ENDFIRSTPART) == 0) break;
            if ( line.compare ("IMAGE") == 0 ) {

                pimage = Obj3dFactory::createObj3d( QString ("IMAGE"), imagesRoot );
                static_cast<ImageItem * > (pimage)->loadFromFile(is);
                static_cast<ImageItem * > (pimage)->initPicture();
                imagesRoot->appendChild( pimage );
                getline ( is, line );
            }
            i++;
        } while ( 1 && i < 20);
        // -------- Images end --
        qDebug() << "END of first part";
#define DEBUG
        // read camera view angle
        //getline ( is, line );
        //int viewangle = std::atoi( line.c_str() );
        //man.fixCamera->setViewAngle(viewangle);
        //man.freeCamera->setViewAngle(viewangle);

        std::string otype;
        while ( !is.eof() )
        {
            // Object factoring magic
            getline ( is, otype );
#ifdef DEBUG
            qDebug() << "Type: " << otype.c_str();
#endif
            getline ( is, line);
#ifdef DEBUG
            qDebug() << "ParentID: " << line.c_str();
#endif

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
    //this->loadBackground(man.getMainGLW(), imagename);
    container->updateModel();
    return true;
}


/*
 * Save whole project to file (txt version)
 *
 *
 * ************************************************************************/
bool Project::saveToFile ( QString & filename ) {
    int objID = 0;
    int level = 0;
    std::ofstream outstream( filename.toStdString());
    if ( !outstream.is_open() )
    {
        qDebug() << "File not openned!";
        return false;
    }

    for ( int i= 0; i < 10; i++ ) {
        outstream << i << std::endl;
    }
 // outstream << this->imagename.toStdString() << std::endl;
 //   outstream << (int) man.fixCamera->getViewAngle() << std::endl;
    saveImagesData ( outstream );
    outstream << ENDFIRSTPART << std::endl;
    saveChildren ( objID, level, objectRoot, outstream );
    outstream.close();
    return true;
}

bool Project::saveImagesData (  std::ofstream & of ) {
   for ( int  i= 0; i < imagesRoot->childCount(); i++ ) {
       imagesRoot->child(i)->saveToFile(of);
       of << "###### check this line!" << std::endl;
   }
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

