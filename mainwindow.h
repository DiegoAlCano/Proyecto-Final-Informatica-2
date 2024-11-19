#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Heroe.h"
#include "Consumible.h"
#include "Enemigo.h"
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QPushButton>

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
    void MenuPrincipal();
    void quitarBotones();
    void mostrarGameOver();
    void mostrarVictoria();
    void mostrarVida(QGraphicsRectItem *barraVidaAmarilla, int vida);

private slots:
    void iniciarNivel1();
    void iniciarNivel2();
    void salirJuego();
private:
    Ui::MainWindow *ui;
    QGraphicsView *vista;
    QGraphicsScene *escena;

    QPushButton *BotonNivel1;
    QPushButton *BotonNivel2;
    QPushButton *BotonNivel3;
    QPushButton *BotonSalir;

};
#endif // MAINWINDOW_H
