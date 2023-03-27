#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "header.h"
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void load_file_slot();
    void cal_slot();
    //void user_guide_slot();
    void submit_slot();


private:
    Ui::MainWindow *ui;
    void connect_cal();
    //slice_file.cpp
    void saveData(string fileName, MatrixXd  matrix);
    MatrixXd openData(string fileToOpen);
    //void sliceMatrixByCircleTime(MatrixXd& srcMatrix);
    void sliceMatrix(MatrixXd& srcMatrixs);

};
#endif // MAINWINDOW_H
