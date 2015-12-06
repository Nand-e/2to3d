#include "itemform.h"
#include "ui_itemform.h"

#include "objectItem.h"
#include "manager.h"

ItemForm::ItemForm(QWidget *parent, Manager * man1) :
    QWidget(parent), man ( *man1 ) ,
    ui(new Ui::ItemForm)
{
    ui->setupUi(this);
    this->obj = 0;
}

void ItemForm::updateData() {

    if ( man.mainproject->actualobject != 0 ) {
        ObjectItem & obj =  *man.mainproject->actualobject;
        ui->item->setText( obj.m_itemData );

        ui->posx->setText( QString::number(obj.getPosition().x() ) );
        ui->posy->setText( QString::number(obj.getPosition().y() ) );
        ui->posz->setText( QString::number(obj.getPosition().z() ) );

  /*      ui->rotx->setText( QString::number(obj.rot.x()) );
        ui->roty->setText( QString::number(obj.rot.y()) );
        ui->rotz->setText( QString::number(obj.rot.z()) );

        ui->sizx->setText( QString::number(obj.scale.x()) );
        ui->sizy->setText( QString::number(obj.scale.y()) );
        ui->sizz->setText( QString::number(obj.scale.z()) );*/
    }

}


ItemForm::~ItemForm()
{
    delete ui;
}

void ItemForm::on_pushButton_clicked()
{
    if ( man.mainproject->actualobject != 0) {
         man.mainproject->actualobject->takeTexture();
    }
}
