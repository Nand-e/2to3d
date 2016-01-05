#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QScrollBar>



namespace Ui {
class MainWindow;
}

class ItemForm;
class Manager;

class GLWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Manager & man, QWidget *parent = 0);
    ~MainWindow();
     ItemForm * itemform;
     GLWidget & getMainGLW ();

private slots:

    void on_pushButton_clicked();
    void on_radioButton_clicked();
    void on_radioButton_2_clicked();
    void on_pushButton_2_clicked();

    void on_actionSave_Project_triggered();

    void on_radioButton_5_clicked();

    void on_radioButton_4_clicked();

    void on_actionNew_project_triggered();

    void on_actionLoad_Project_triggered();

    void on_Resetfreecamera_clicked();


    void on_FreeCamButton_toggled(bool checked);

    void on_ItemMovementB_toggled(bool checked);

private:
    QScrollBar     * scroll;
    GLWidget       * mainGLW;
    GLWidget       * currentGlWidget;
    Ui::MainWindow * ui;
    Manager        & man;
};

#endif // MAINWINDOW_H
