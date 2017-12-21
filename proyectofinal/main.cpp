#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString file_name;
    MainWindow w;
    w.show();

    return a.exec();
}
