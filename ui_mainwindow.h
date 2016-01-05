/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSave_Project;
    QAction *actionNew_project;
    QAction *actionLoad_Project;
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLCDNumber *lcdNumber;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *ItemLay;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *ItemLay_2;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QToolButton *ItemMovementB;
    QToolButton *FreeCamButton;
    QToolButton *ImageCamB;
    QToolButton *Resetfreecamera;
    QVBoxLayout *verticalLayout_4;
    QRadioButton *radioButton_5;
    QRadioButton *radioButton_4;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1043, 563);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(500, 500));
        MainWindow->setStyleSheet(QLatin1String("#centralwidget{\n"
"border: 1px solid gray;\n"
"border-radius: 2px;\n"
"background: white;\n"
"background: QLinearGradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #eef, stop: 1 #22f);\n"
"}\n"
""));
        actionSave_Project = new QAction(MainWindow);
        actionSave_Project->setObjectName(QStringLiteral("actionSave_Project"));
        actionNew_project = new QAction(MainWindow);
        actionNew_project->setObjectName(QStringLiteral("actionNew_project"));
        actionLoad_Project = new QAction(MainWindow);
        actionLoad_Project->setObjectName(QStringLiteral("actionLoad_Project"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy1);
        centralwidget->setMinimumSize(QSize(500, 500));
        centralwidget->setMaximumSize(QSize(2000, 1200));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(870, 370, 161, 141));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lcdNumber = new QLCDNumber(verticalLayoutWidget);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));

        verticalLayout->addWidget(lcdNumber);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));

        verticalLayout->addLayout(horizontalLayout_2);

        verticalLayoutWidget_2 = new QWidget(centralwidget);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(870, 20, 161, 341));
        ItemLay = new QVBoxLayout(verticalLayoutWidget_2);
        ItemLay->setObjectName(QStringLiteral("ItemLay"));
        ItemLay->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(180, 70, 681, 441));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(0, 0, 9, 0);
        verticalLayoutWidget_3 = new QWidget(centralwidget);
        verticalLayoutWidget_3->setObjectName(QStringLiteral("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(10, 20, 161, 491));
        ItemLay_2 = new QVBoxLayout(verticalLayoutWidget_3);
        ItemLay_2->setObjectName(QStringLiteral("ItemLay_2"));
        ItemLay_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_2 = new QWidget(centralwidget);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(180, 20, 681, 44));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(1);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setSizeConstraint(QLayout::SetDefaultConstraint);
        ItemMovementB = new QToolButton(horizontalLayoutWidget_2);
        ItemMovementB->setObjectName(QStringLiteral("ItemMovementB"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/ImageRotation.png"), QSize(), QIcon::Active, QIcon::Off);
        icon.addFile(QStringLiteral(":/images/ImageRotation.png"), QSize(), QIcon::Active, QIcon::On);
        ItemMovementB->setIcon(icon);
        ItemMovementB->setIconSize(QSize(32, 32));
        ItemMovementB->setCheckable(true);

        horizontalLayout_4->addWidget(ItemMovementB);

        FreeCamButton = new QToolButton(horizontalLayoutWidget_2);
        FreeCamButton->setObjectName(QStringLiteral("FreeCamButton"));
        FreeCamButton->setText(QStringLiteral("FreeCamera"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/FreeCam.png"), QSize(), QIcon::Active, QIcon::Off);
        icon1.addFile(QStringLiteral(":/images/FreeCam.png"), QSize(), QIcon::Active, QIcon::On);
        FreeCamButton->setIcon(icon1);
        FreeCamButton->setIconSize(QSize(32, 32));
        FreeCamButton->setCheckable(true);
        FreeCamButton->setAutoRaise(false);

        horizontalLayout_4->addWidget(FreeCamButton);

        ImageCamB = new QToolButton(horizontalLayoutWidget_2);
        ImageCamB->setObjectName(QStringLiteral("ImageCamB"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/ImageCam.png"), QSize(), QIcon::Active, QIcon::Off);
        icon2.addFile(QStringLiteral(":/images/ImageCam.png"), QSize(), QIcon::Active, QIcon::On);
        ImageCamB->setIcon(icon2);
        ImageCamB->setIconSize(QSize(32, 32));
        ImageCamB->setCheckable(true);

        horizontalLayout_4->addWidget(ImageCamB);

        Resetfreecamera = new QToolButton(horizontalLayoutWidget_2);
        Resetfreecamera->setObjectName(QStringLiteral("Resetfreecamera"));

        horizontalLayout_4->addWidget(Resetfreecamera);


        horizontalLayout_3->addLayout(horizontalLayout_4);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        radioButton_5 = new QRadioButton(horizontalLayoutWidget_2);
        radioButton_5->setObjectName(QStringLiteral("radioButton_5"));

        verticalLayout_4->addWidget(radioButton_5);

        radioButton_4 = new QRadioButton(horizontalLayoutWidget_2);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));

        verticalLayout_4->addWidget(radioButton_4);


        horizontalLayout_3->addLayout(verticalLayout_4);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1043, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionNew_project);
        menuFile->addAction(actionLoad_Project);
        menuFile->addAction(actionSave_Project);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionSave_Project->setText(QApplication::translate("MainWindow", "Save Project", 0));
        actionNew_project->setText(QApplication::translate("MainWindow", "New project", 0));
        actionLoad_Project->setText(QApplication::translate("MainWindow", "Load Project", 0));
        ItemMovementB->setText(QApplication::translate("MainWindow", "...", 0));
        ImageCamB->setText(QApplication::translate("MainWindow", "...", 0));
        Resetfreecamera->setText(QApplication::translate("MainWindow", "Reset Free Camera", 0));
        radioButton_5->setText(QApplication::translate("MainWindow", "Edges", 0));
        radioButton_4->setText(QApplication::translate("MainWindow", "No Edges", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
