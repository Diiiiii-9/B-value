#include "mainwindow.h"
#include "regression.h"
#include <QApplication>

Matrix<double, Dynamic, Dynamic> final_E_value;
std::vector<double> final_vec;
MatrixXd matrix_source;
string input_file;
int interv;
int m;
int flag = 2;   //待计算的数据列数

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
