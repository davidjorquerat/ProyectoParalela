#ifndef FIXTURE_H
#define FIXTURE_H

#include <QMainWindow>

namespace Ui {
class fixture;
}

class fixture : public QMainWindow
{
    Q_OBJECT

public:
    explicit fixture(QWidget *parent = 0);
    ~fixture();

private slots:
    void on_Cargar_clicked();


private:
    Ui::fixture *ui;
};

#endif // FIXTURE_H
