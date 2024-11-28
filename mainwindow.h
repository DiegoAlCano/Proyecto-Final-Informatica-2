#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Personaje.h"
#include "Heroe.h"
#include "Consumible.h"
#include "Enemigo.h"
#include "Proyectil.h"
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QPushButton>
#include <QList>

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
    void mostrarGameOver(QGraphicsScene *escenaActual);
    void mostrarVictoria(QGraphicsScene *escenaActual);
    void mostrarVida(QGraphicsRectItem *barraVidaAmarilla, int vida);
    void iniciarSegundaParteNivel2(QGraphicsScene *escenaActual);
    void añadirElementoGrafico(QGraphicsScene *escenaActual, int posX, int posY, const QString &rutaImagen);
    void añadirBarrasVida(QGraphicsScene *escenaActual, int posX, int posY, QGraphicsRectItem *&barraVidaRoja, QGraphicsRectItem *&barraVidaAmarilla);
    void detenerTimers();

private slots:
    void iniciarNivel1();
    void iniciarNivel2();
    void iniciarNivel3();
    void salirJuego();

private:
    Ui::MainWindow *ui;
    QGraphicsView *vista;
    QGraphicsScene *escena;

    QPushButton *BotonNivel1;
    QPushButton *BotonNivel2;
    QPushButton *BotonNivel3;
    QPushButton *BotonSalir;

    //Para el nivel 3 - Control del flujo de las salas
    bool fondoCambiado1;
    bool fondoCambiado2;
    bool sala1;
    bool sala2;

    QList<QTimer*> timers;


};
#endif // MAINWINDOW_H
