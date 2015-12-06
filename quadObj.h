#ifndef ITEM2_H
#define ITEM2_H

#include "glwidget.h"
#include "emptyobj.h"

class QKeyEvent;
class QMatrix4x4;
class QPixmap;
class Project;

class QuadObj : public EmptyObj {

public:
    QuadObj(const QString data, ObjectItem *parent, Project & pro1);
    ~QuadObj ();

    virtual std::string getType() const;
    virtual void drawgl(GLWidget &gl, QMatrix4x4 & cameramat  );
    virtual void makeobject ();
    virtual void takeTexture ();
    virtual bool loadFromFile (std::ifstream & inputstream);
    virtual bool saveToFile   (std::ofstream & outstream);

    Project & pro;
};

#endif // ITEM2_H
