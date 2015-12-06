#ifndef OBJ3DFACTORY_H
#define OBJ3DFACTORY_H




#include <QString>
#include <QVector>

class ObjectItem;
class Project;

class Obj3dFactory
{
public:
    Obj3dFactory(Project * pro1 );
    static QVector<QString> &  classNames ();
    static ObjectItem *createObj3d (QString &  str , ObjectItem *parent);

private:
    static Project * pro;
    static QVector<QString> names;

};

#endif // OBJ3DFACTORY_H
