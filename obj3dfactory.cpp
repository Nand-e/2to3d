#include "obj3dfactory.h"



#include "quadObj.h"
#include "cubeObj.h"
#include "imageitem.h"

Obj3dFactory::Obj3dFactory( Project * pro1)
{
    pro = pro1;
    names.push_back("QUAD");
    names.push_back("CUBE");

}

ObjectItem * Obj3dFactory::createObj3d(QString &type, ObjectItem * parent, QString & name, QString & data ) {

   if ( pro == 0 ) {
     qDebug() << "Error: The Factory not inited!" ;
   }


   if ( type.compare("IMAGE") == 0 ) {
       qDebug() << "Image created" ;
       return new ImageItem ( name, data , parent, * pro );

   }

   if ( type.compare("QUAD") == 0 ) {
        qDebug() << "QUAD created" ;
        return new QuadObj ( QString ("quad"), parent , *pro );

   }
   if ( type.compare("CUBE") == 0 ) {
        qDebug() << "CUBE created" ;
        return new CubeObj ( QString ("cube" ), parent , *pro );

   }

   return 0;
}
QVector<QString> & Obj3dFactory::classNames() {
    return names;
}


Project * Obj3dFactory::pro = 0;
QVector<QString> Obj3dFactory::names;
