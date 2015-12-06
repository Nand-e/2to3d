#ifndef PROJECTMODELL_H
#define PROJECTMODELL_H


#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

class ObjectItem;
class Project;

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit TreeModel(QObject *parent, Project *pro);
    ~TreeModel();

    ObjectItem *  getRoot ();
    QVariant      data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    QVariant      headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QModelIndex   index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QModelIndex   parent(const QModelIndex &index) const Q_DECL_OVERRIDE;
    int           rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int           columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    bool          insertRow(int row, const QModelIndex & parent = QModelIndex());


    void clearAlldata();
    void createRootItems ();
    void updateModel ();
    ObjectItem *  rootItem;             // TODO
    Project    *  pro;
private:



};

#endif // PROJECTMODELL_H
