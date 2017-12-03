#include "fixture.h"
#include "ui_fixture.h"
#include <math.h>
#include <fstream>



fixture::fixture(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::fixture)
{
    ui->setupUi(this);
}

fixture::~fixture()
{
    delete ui;
}

void fixture::on_Cargar_clicked()
{

}
