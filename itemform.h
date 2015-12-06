#ifndef ITEMFORM_H
#define ITEMFORM_H

#include <QWidget>

class ObjectItem;
class Manager;

namespace Ui {
class ItemForm;
}

class ItemForm : public QWidget
{
    Q_OBJECT
public:
    explicit ItemForm(QWidget *parent = 0, Manager * man =  0   );
    void updateData();
    ~ItemForm();
private slots:
    void on_pushButton_clicked();

private:
    Ui::ItemForm * ui;
    ObjectItem   * obj;
    Manager & man;

};

#endif // ITEMFORM_H
