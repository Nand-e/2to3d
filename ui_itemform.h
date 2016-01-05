/********************************************************************************
** Form generated from reading UI file 'itemform.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ITEMFORM_H
#define UI_ITEMFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ItemForm
{
public:
    QFrame *frame;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QPushButton *pushButton;
    QLabel *Item;
    QLineEdit *item;
    QLabel *Type;
    QLineEdit *type;
    QLineEdit *posx;
    QLineEdit *posy;
    QLineEdit *posz;
    QLineEdit *rotx;
    QLineEdit *roty;
    QLineEdit *rotz;
    QLineEdit *sizx;
    QLineEdit *sizy;
    QLineEdit *sizz;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_4;

    void setupUi(QWidget *ItemForm)
    {
        if (ItemForm->objectName().isEmpty())
            ItemForm->setObjectName(QStringLiteral("ItemForm"));
        ItemForm->resize(161, 309);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ItemForm->sizePolicy().hasHeightForWidth());
        ItemForm->setSizePolicy(sizePolicy);
        ItemForm->setMaximumSize(QSize(400, 600));
        ItemForm->setStyleSheet(QLatin1String("QLineEdit {\n"
"padding: 1px;\n"
"border-style: solid;\n"
"border: 1px solid gray;\n"
"border-radius: 2px;\n"
"}\n"
"\n"
""));
        frame = new QFrame(ItemForm);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(0, 0, 161, 301));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        QFont font;
        font.setPointSize(6);
        frame->setFont(font);
        frame->setStyleSheet(QLatin1String("#frame{\n"
"border:1px solid gray;\n"
"border-radius: px;\n"
"background: white;\n"
"background: QLinearGradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #eef, stop: 1 #22f);\n"
"}\n"
"\n"
"QLineEdit {\n"
"padding: 1px;\n"
"border-style: solid;\n"
"border: 1px solid gray;\n"
"border-radius: 2px;\n"
"}"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayoutWidget_2 = new QWidget(frame);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(10, 190, 141, 101));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(verticalLayoutWidget_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setEnabled(true);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMaximumSize(QSize(200, 20));
        label_2->setFrameShape(QFrame::StyledPanel);
        label_2->setLineWidth(2);
        label_2->setMargin(0);

        verticalLayout_2->addWidget(label_2, 0, Qt::AlignHCenter);

        pushButton = new QPushButton(frame);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(10, 130, 141, 23));
        Item = new QLabel(frame);
        Item->setObjectName(QStringLiteral("Item"));
        Item->setGeometry(QRect(10, 20, 41, 16));
        sizePolicy1.setHeightForWidth(Item->sizePolicy().hasHeightForWidth());
        Item->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setPointSize(8);
        font1.setBold(true);
        font1.setWeight(75);
        Item->setFont(font1);
        item = new QLineEdit(frame);
        item->setObjectName(QStringLiteral("item"));
        item->setGeometry(QRect(40, 20, 31, 15));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(item->sizePolicy().hasHeightForWidth());
        item->setSizePolicy(sizePolicy2);
        item->setMaximumSize(QSize(16777215, 15));
        item->setFont(font);
        Type = new QLabel(frame);
        Type->setObjectName(QStringLiteral("Type"));
        Type->setGeometry(QRect(80, 20, 31, 16));
        sizePolicy1.setHeightForWidth(Type->sizePolicy().hasHeightForWidth());
        Type->setSizePolicy(sizePolicy1);
        QFont font2;
        font2.setPointSize(8);
        Type->setFont(font2);
        type = new QLineEdit(frame);
        type->setObjectName(QStringLiteral("type"));
        type->setGeometry(QRect(110, 20, 41, 15));
        sizePolicy2.setHeightForWidth(type->sizePolicy().hasHeightForWidth());
        type->setSizePolicy(sizePolicy2);
        type->setMaximumSize(QSize(16777215, 15));
        type->setFont(font);
        posx = new QLineEdit(frame);
        posx->setObjectName(QStringLiteral("posx"));
        posx->setGeometry(QRect(40, 50, 31, 15));
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(posx->sizePolicy().hasHeightForWidth());
        posx->setSizePolicy(sizePolicy3);
        posx->setMaximumSize(QSize(16777215, 15));
        posx->setFont(font);
        posy = new QLineEdit(frame);
        posy->setObjectName(QStringLiteral("posy"));
        posy->setGeometry(QRect(80, 50, 31, 15));
        sizePolicy2.setHeightForWidth(posy->sizePolicy().hasHeightForWidth());
        posy->setSizePolicy(sizePolicy2);
        posy->setMaximumSize(QSize(16777215, 15));
        posy->setFont(font);
        posz = new QLineEdit(frame);
        posz->setObjectName(QStringLiteral("posz"));
        posz->setGeometry(QRect(120, 50, 31, 15));
        sizePolicy2.setHeightForWidth(posz->sizePolicy().hasHeightForWidth());
        posz->setSizePolicy(sizePolicy2);
        posz->setMaximumSize(QSize(16777215, 15));
        posz->setFont(font);
        rotx = new QLineEdit(frame);
        rotx->setObjectName(QStringLiteral("rotx"));
        rotx->setGeometry(QRect(40, 70, 31, 15));
        sizePolicy2.setHeightForWidth(rotx->sizePolicy().hasHeightForWidth());
        rotx->setSizePolicy(sizePolicy2);
        rotx->setMaximumSize(QSize(16777215, 15));
        rotx->setFont(font);
        roty = new QLineEdit(frame);
        roty->setObjectName(QStringLiteral("roty"));
        roty->setGeometry(QRect(80, 70, 31, 15));
        sizePolicy2.setHeightForWidth(roty->sizePolicy().hasHeightForWidth());
        roty->setSizePolicy(sizePolicy2);
        roty->setMaximumSize(QSize(16777215, 15));
        roty->setFont(font);
        rotz = new QLineEdit(frame);
        rotz->setObjectName(QStringLiteral("rotz"));
        rotz->setGeometry(QRect(120, 70, 31, 15));
        sizePolicy2.setHeightForWidth(rotz->sizePolicy().hasHeightForWidth());
        rotz->setSizePolicy(sizePolicy2);
        rotz->setMaximumSize(QSize(16777215, 15));
        rotz->setFont(font);
        sizx = new QLineEdit(frame);
        sizx->setObjectName(QStringLiteral("sizx"));
        sizx->setGeometry(QRect(40, 90, 31, 15));
        sizePolicy2.setHeightForWidth(sizx->sizePolicy().hasHeightForWidth());
        sizx->setSizePolicy(sizePolicy2);
        sizx->setMaximumSize(QSize(16777215, 15));
        sizx->setFont(font);
        sizy = new QLineEdit(frame);
        sizy->setObjectName(QStringLiteral("sizy"));
        sizy->setGeometry(QRect(80, 90, 31, 15));
        sizePolicy2.setHeightForWidth(sizy->sizePolicy().hasHeightForWidth());
        sizy->setSizePolicy(sizePolicy2);
        sizy->setMaximumSize(QSize(16777215, 15));
        sizy->setFont(font);
        sizz = new QLineEdit(frame);
        sizz->setObjectName(QStringLiteral("sizz"));
        sizz->setGeometry(QRect(120, 90, 31, 15));
        sizePolicy2.setHeightForWidth(sizz->sizePolicy().hasHeightForWidth());
        sizz->setSizePolicy(sizePolicy2);
        sizz->setMaximumSize(QSize(16777215, 15));
        sizz->setFont(font);
        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 50, 31, 20));
        label_3 = new QLabel(frame);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 70, 31, 20));
        label_4 = new QLabel(frame);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 90, 31, 20));

        retranslateUi(ItemForm);

        QMetaObject::connectSlotsByName(ItemForm);
    } // setupUi

    void retranslateUi(QWidget *ItemForm)
    {
        ItemForm->setWindowTitle(QApplication::translate("ItemForm", "Form", 0));
        label_2->setText(QApplication::translate("ItemForm", "Texture", 0));
        pushButton->setText(QApplication::translate("ItemForm", "Take texture", 0));
        Item->setText(QApplication::translate("ItemForm", "Item", 0));
        Type->setText(QApplication::translate("ItemForm", "Type", 0));
        label->setText(QApplication::translate("ItemForm", "Pos", 0));
        label_3->setText(QApplication::translate("ItemForm", "Rot", 0));
        label_4->setText(QApplication::translate("ItemForm", "Size", 0));
    } // retranslateUi

};

namespace Ui {
    class ItemForm: public Ui_ItemForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ITEMFORM_H
