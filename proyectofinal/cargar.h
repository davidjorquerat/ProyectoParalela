#ifndef CARGAR_H
#define CARGAR_H

#include <QMainWindow>

namespace Ui {
class Cargar;
}

class Cargar : public QMainWindow
{
    Q_OBJECT

public:
    explicit Cargar(QWidget *parent = 0);
    ~Cargar();

private:
    Ui::Cargar *ui;
};

#endif // CARGAR_H
