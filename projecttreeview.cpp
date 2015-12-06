#include "projecttreeview.h"
#include <QDebug>

#include <QMenu>
#include "obj3dfactory.h"

ProjectTreeView::ProjectTreeView(QObject *parent)
{
   this->setContextMenuPolicy(Qt::CustomContextMenu);
   connect( this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onCustomContextMenu(QPoint)));
}

void  ProjectTreeView::onCustomContextMenu(QPoint pos) {
       QMenu menu; // = new QMenu;
       QPoint globalPos = this->mapToGlobal(pos);

       QAction  * act;
       foreach ( QString str, Obj3dFactory::classNames() ) {
         QAction  * act =  new QAction ( QString ( "Add ") + QString ( str ),0 );
         act->setData( str );
         menu.addAction( act );
       }
       act =  menu.exec(globalPos);

       if ( act != 0) {
        qDebug () << act->data();
        // call the factorz with it, and the parent
       }
}

void ProjectTreeView::slotTest (int i) {
    qDebug() << i ;
}
