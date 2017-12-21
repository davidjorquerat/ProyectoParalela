#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QProcess>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QProcess *proceso;
    QString file_name;



public slots:
    void abrirCargar();

private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
};

#endif // MAINWINDOW_H
