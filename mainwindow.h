#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Heroe.h"
#include "Consumible.h"
#include "Enemigo.h"
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_1_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsView *vista;
    QGraphicsScene *escena;

};
#endif // MAINWINDOW_H
