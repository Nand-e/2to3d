#ifndef PROJECTTREEVIEW_H
#define PROJECTTREEVIEW_H

#include <QObject>
#include <QTreeView>

class Manager;

class ProjectTreeView : public QTreeView
{   
    Q_OBJECT
public:
    explicit ProjectTreeView(QObject *parent, Manager & man1);

signals:

public slots:
    void onCustomContextMenu( QPoint );

    void slotTest (int);

private:
    Manager & man;

};

#endif // PROJECTTREEVIEW_H
