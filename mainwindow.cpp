#include "mainwindow.h"
#include "header.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect_cal();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connect_cal()
{
    connect(ui->file_pushButton,&QPushButton::clicked,this,&MainWindow::load_file_slot);
    connect(ui->OK_pushButton,&QPushButton::clicked,this,&MainWindow::cal_slot);
    connect(ui->Submit_pushButton,&QPushButton::clicked,this,&MainWindow::submit_slot);
}



void MainWindow::load_file_slot()
{

    QString fileName = QFileDialog::getOpenFileName(this, tr("选择输入文件"), "D:", tr("csv文件(*csv)"));
    input_file = fileName.toStdString();
    if(input_file.empty())
    {
        ui->textBrowser->insertPlainText("不存在输入的文件/未选择文件");
        ui->textBrowser->moveCursor(QTextCursor::End);
        ui->textBrowser->append(QString(""));
        return;
    }

    ui->file_line_edit->setText(input_file.c_str());
    matrix_source = openData(input_file);

}

void MainWindow::cal_slot()
{

    if(input_file.empty())
    {
        cout << "plz input your file." << endl;
        ui->textBrowser->insertPlainText("未载入文件，请先选择文件，等待选择框出现选中文件名称后再进行计算");
        ui->textBrowser->moveCursor(QTextCursor::End);
        ui->textBrowser->append(QString(""));
        return;
    }
    final_vec.clear();

    if(matrix_source.size() == 0)
    {
        return;
    }
    sliceMatrix(matrix_source);

    int sizeOfVec = final_vec.size();
    final_E_value = Map<MatXXdR>(final_vec.data(), sizeOfVec / flag, flag);

    string out_source = input_file + "_output_file.csv";

    ui->textBrowser->insertPlainText("计算成功！");
    ui->textBrowser->moveCursor(QTextCursor::End);
    ui->textBrowser->append(QString(""));

    saveData(out_source, final_E_value);
}


void MainWindow::submit_slot()
{
    QString S_interv = ui->interv_Line->text();
    QString S_m = ui->width_Line->text();

    interv = S_interv.toInt();
    m = S_m.toInt();
}
