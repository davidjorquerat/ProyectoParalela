#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cargar.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QDebug>
#include <cstring>

QString file_name2;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    proceso = new QProcess(this);

    QString file_name2;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::abrirCargar(){

    Cargar *cargar = new Cargar();
    cargar ->show();

}

void MainWindow::on_pushButton_3_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,"Open a file","C://");
    file_name2= file_name;


    QMessageBox::information(this,"..",file_name);



}

void MainWindow::on_pushButton_2_clicked()
{

    QStringList a;
    a.append(file_name2);
    a.append("~");
    proceso->start("fixt",a);//fixt es el nombre del archivo ejecutable que se crea al compilar el fixture
    QMessageBox::information(this,"..","ESTOY LISTO");


}
