
#include "treemodel.h"
#include "ObjectItem.h"
#include "QuadObj.h"

#include <QStringList>
#include <QDebug>



TreeModel::TreeModel(QObject *parent, Project * pro1 )
    : QAbstractItemModel(parent), pro ( pro1 )
{
    rootItem = new QuadObj("Header", 0 , * pro );
}

TreeModel::~TreeModel()
{
    delete rootItem;
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<ObjectItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}


QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    ObjectItem *item = static_cast<ObjectItem*>(index.internalPointer());

    return item->data(index.column());
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return QAbstractItemModel::flags(index);
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent)
            const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    ObjectItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<ObjectItem*>(parent.internalPointer());

    ObjectItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

ObjectItem *TreeModel::getRoot() {
    return rootItem;
}

bool TreeModel::insertRow(int row, const QModelIndex &parent) {
    qDebug() << "Insert Row";
    return true;
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    ObjectItem *childItem = static_cast<ObjectItem*>(index.internalPointer());
    ObjectItem *parentItem = childItem->parentItem();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->rowinParentList(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    ObjectItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<ObjectItem*>(parent.internalPointer());

    return parentItem->childCount();
}


/*
 * Delete All item apartf from rootItem
 * *****************************************/
void TreeModel::clearAlldata( ObjectItem * item) {
  beginResetModel();
  item->deleteChildren();
  endResetModel();
}

void TreeModel::updateModel () {
        this->beginResetModel();
      this->endResetModel();
}

bool TreeModel::addObject(ObjectItem * item ) {
     QModelIndex parentIndex = createIndex(item->parentItem()->rowinParentList() ,0,
                                           item->parentItem() );

     beginInsertRows(parentIndex, item->parentItem()->childCount(), item->parentItem()->childCount() );
     item->parentItem()->appendChild( item );
     endInsertRows();
     return true;
}

bool TreeModel::deleteObject(ObjectItem * item) {

    QModelIndex pindex =  createIndex(item->parentItem()->rowinParentList(),0,
                                      item->parentItem());

    this->beginRemoveRows(pindex,item->rowinParentList(), item->rowinParentList() );
    item->parentItem()->deleteChild ( item ) ;
    this->endRemoveRows();
    return true;
}


