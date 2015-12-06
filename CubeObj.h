#ifndef CubeObj_H
#define CubeObj_H

#include "emptyObj.h"
#include <string>

class Project;

class CubeObj : public EmptyObj
{
public:
   // CubeObj();
    CubeObj(const QString name, ObjectItem *parent, Project & pro);
    ~CubeObj();

    virtual std::string getType() const;
    virtual void drawgl(GLWidget &gl, QMatrix4x4 & cameramat  );
    virtual void makeobject ();
    virtual bool loadFromFile(std::ifstream & inputstream);
    virtual bool saveToFile(std::ofstream & outstream);    
    virtual void takeTexture();

    void UvtoCvCoordinate (cv::Mat & input, QVector<QVector2D> & inPoints, cv::Point2f * output  );

private:
    Project & pro;
    unsigned int textureIDs[6];
};

#endif // CubeObj_H
