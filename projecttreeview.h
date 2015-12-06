#ifndef PROJECTTREEVIEW_H
#define PROJECTTREEVIEW_H

#include <QObject>
#include <QTreeView>

class ProjectTreeView : public QTreeView
{   
    Q_OBJECT
public:
    explicit ProjectTreeView(QObject *parent = 0);

signals:

public slots:
    void onCustomContextMenu( QPoint );
    void slotTest (int);

};

#endif // PROJECTTREEVIEW_H
