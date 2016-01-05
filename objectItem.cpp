#include "objectItem.h"


ObjectItem::ObjectItem(const QString data, ObjectItem *parent)
{
    m_parentItem = parent;
    m_itemData   = data;
}


ObjectItem::~ObjectItem()
{
    //qDebug() << "delete" << this->m_itemData;
    qDeleteAll(m_childItems);
}

std::string ObjectItem::getType() const { return std::string("ObjectItem"); }


void ObjectItem::appendChild(ObjectItem *item)
{
    m_childItems.append( item);
}


ObjectItem * ObjectItem::child(int row)
{
    return m_childItems.value(row);
}

int ObjectItem::childCount() const
{
    return m_childItems.count();
}


int ObjectItem::columnCount() const
{
    return 1 ; // m_itemData.count();
}

QVariant ObjectItem::data(int column) const
{
    QString str;
    str = m_itemData + QString(" - "); //+ getType();
    str += QString::fromStdString( this->getType() );
    return QVariant ( str );
}

ObjectItem *ObjectItem::parentItem()
{
    return m_parentItem;
}

int ObjectItem::rowinParentList() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<ObjectItem *> ( this));

    return 0;
}

void ObjectItem::deleteChildren() {
    for ( int i=0; i < this->m_childItems.size() ; i++ ) {
        delete m_childItems.at(i);
    }
    m_childItems.clear();
}


bool ObjectItem::deleteChild ( ObjectItem * item) {


    m_childItems.removeOne( item );
   delete item;
    return true;
}


void ObjectItem::drawgl ( GLWidget  &gl, QMatrix4x4 &mat ) { return; }
QMatrix4x4  ObjectItem::getMatrix() { return QMatrix4x4();}

