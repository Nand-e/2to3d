#include "mainwindow.h"
#include "ui_mainwindow.h"



#include <QtWidgets>

#include "itemform.h"
#include "glwidget.h"
#include "window.h"
#include "projecttreeview.h"
#include "manager.h"
#include "treemodel.h"

MainWindow::MainWindow(Manager & man1, QWidget *parent) :
    QMainWindow(parent), man (man1) ,
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scroll   = new QScrollBar ( Qt::Horizontal );
    itemform = new ItemForm ( this , & man1 );
    mainGLW  = new GLWidget ( this, 0 , man1);                  // Create GL Widget
    ui->horizontalLayout->addWidget(mainGLW);
    ui->verticalLayout->addWidget( scroll );
    ui->ItemLay_2->addWidget( man.ptreeview );
    ui->ItemLay->addWidget( itemform);

    QTimer *timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), mainGLW, SLOT(updateGL()) );

    scroll->setValue( man.freeCamera->getViewAngle());
    connect(scroll, SIGNAL(valueChanged(int)), man.freeCamera , SLOT(setViewAngle(int)) );
    connect(scroll, SIGNAL(valueChanged(int)), man.mainproject , SLOT(setViewAngle(int)) );
    connect(scroll, SIGNAL(valueChanged(int)), ui->lcdNumber, SLOT(display(int)));

    timer->start(20);
    setWindowTitle(tr("Textures"));
}


MainWindow::~MainWindow()
{
    delete ui;
}

GLWidget & MainWindow::getMainGLW() {
    return *mainGLW;
}

void MainWindow::on_pushButton_clicked()
{
  // man.mainproject->loadBackground(*this->mainGLW);
}

void MainWindow::on_radioButton_clicked()
{
    man.keycontrol = man.CameraControl;
}

void MainWindow::on_radioButton_2_clicked()
{
    man.keycontrol = man.ItemControl;
}



void MainWindow::on_actionSave_Project_triggered()
{
  QString fileName = QFileDialog::getSaveFileName(this, 0 ,tr ("Project File *.txt") );
  man.mainproject->saveToFile( fileName);
}

void MainWindow::on_radioButton_5_clicked()
{
    man.edges = true;
}

void MainWindow::on_radioButton_4_clicked()
{
    man.edges = false;
}

void MainWindow::on_actionNew_project_triggered() {
    man.mainproject->clearProject();
}

void MainWindow::on_actionLoad_Project_triggered()
{

    QString fileName = QFileDialog::getOpenFileName(this,
                              tr("Open Project"), "Projects", tr("Project file (*.txt)"));
    man.mainproject->loadFile( fileName);

}

// Select free camera
void MainWindow::on_toolButton_2_clicked()
{
     man.mainproject->setFreecam( true );
    // man.actualCamera = man.freeCamera;
     man.keycontrol   = man.CameraControl;

     ui->radioButton_2->setChecked( true );
}

// deselect free cam
void MainWindow::on_pushButton_2_clicked()
{
    man.mainproject->setFreecam( false );
}

void MainWindow::on_Resetfreecamera_clicked()
{
    * man.freeCamera = *man.actualCamera;  //
}
