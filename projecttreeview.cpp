#include "projecttreeview.h"
#include <QDebug>

#include <QMenu>
#include <QModelIndex>
#include "obj3dfactory.h"

#include "objectItem.h"
#include "manager.h"
#include "treemodel.h"

ProjectTreeView::ProjectTreeView(QObject *parent, Manager &man1) :
    man (man1)
{  
   this->setContextMenuPolicy(Qt::CustomContextMenu);
   connect( this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onCustomContextMenu(QPoint)));
}

void  ProjectTreeView::onCustomContextMenu(QPoint pos) {
       QMenu menu; // = new QMenu;
       QPoint globalPos = this->mapToGlobal(pos);

       QAction  * act1 =  new QAction ( QString ( "Add ")   + QString ( "Image" ),0 );
       QAction  * act2 =  new QAction ( QString ( "Delete") , 0  ); //+ QString ( "" ),0 );
       act1->setData( "Image" );
       menu.addAction ( act1 );
       menu.addAction ( act2 );
       menu.addSeparator();

       QAction  * act;
       foreach ( QString str, Obj3dFactory::classNames() ) {
         act =  new QAction ( QString ( "Add ") + QString ( str ),0 );
         act->setData( str );
         menu.addAction( act );
       }
       act =  menu.exec(globalPos);

       if ( act != 0) {
            if ( act == act1 ) {
                man.mainproject->addImage();
            }
            else if ( act == act2 ) {
                 ObjectItem * pobject = static_cast<ObjectItem *> ( currentIndex().internalPointer() );
                 man.mainproject->deleteObject( pobject );
            }
            else
            {
                qDebug()<< "Create";
                ObjectItem * pParent = static_cast<ObjectItem *> ( currentIndex().internalPointer() );
                ObjectItem * pItem = Obj3dFactory::createObj3d( act->data().toString() , pParent );
                man.mainproject->addObject( pItem  );
            }
       }
}

void ProjectTreeView::slotTest (int i) {
    qDebug() << i ;
}
