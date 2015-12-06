#include "obj3dfactory.h"



#include "quadObj.h"
#include "cubeObj.h"

Obj3dFactory::Obj3dFactory( Project * pro1)
{
    pro = pro1;
    names.push_back("QUAD");
    names.push_back("CUBE");

}

ObjectItem * Obj3dFactory::createObj3d(QString &str, ObjectItem * parent ) {
   if ( pro != 0 ) {
     qDebug() << "Error: The Factory not inited!" ;
   }
   if ( str.compare("QUAD") ) {
        return new QuadObj ( QString ("quad"), parent , *pro );
   }
   if ( str.compare("CUBE") ) {
        return new CubeObj ( QString ("cube" ), parent , *pro );
   }


}
QVector<QString> & Obj3dFactory::classNames() {
    return names;
}


Project * Obj3dFactory::pro = 0;
QVector<QString> Obj3dFactory::names;
