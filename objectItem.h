#ifndef ITEM_H
#define ITEM_H

#include <QList>
#include <QVariant>
#include <QMatrix4x4>

#include <fstream>

class GLWidget;
class QKeyEvent;


class ObjectItem
{
public:
    explicit ObjectItem(const QString data, ObjectItem *parentItem = 0);
    virtual ~ObjectItem();

    void appendChild(ObjectItem *child);

    ObjectItem * parentItem();
    ObjectItem * child(int row);
    int  childCount() const;
    int  columnCount() const;
    void deleteChildren();
    bool deleteChild ( ObjectItem * );
    int  rowinParentList() const;
    QVariant data(int column) const;  

    // This inmplemented in Empty Item
    virtual QVector3D & getPosition () = 0;
    virtual QVector3D & getScale()     = 0;
    virtual QMatrix4x4 getMatrix()     = 0;
    virtual bool manipulate (QKeyEvent *event) = 0;
    virtual void step (QVector3D & vect) = 0;

    // This implemented in each 3d object
    virtual void takeTexture () = 0;
    virtual std::string getType() const;
    virtual void drawgl ( GLWidget  &gl, QMatrix4x4 &mat ) = 0;
    virtual bool saveToFile  (std::ofstream & of ) = 0;
    virtual bool loadFromFile(std::ifstream & ifs) = 0;


    QString  m_itemData;
protected:
    QList<ObjectItem *> m_childItems;
    ObjectItem *m_parentItem;
};

 /* ObjectItem
         |
         V
    EmptyItem
         |
         V
    3dItems


 */





#endif
