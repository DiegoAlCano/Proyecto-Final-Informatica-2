#ifndef PROYECTIL_H
#define PROYECTIL_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include "Enemigo.h"

class Proyectil : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

private:
    //Variables para el movimiento
    double x;
    double y;
    double vx;
    double vy;
    double v0;
    double tiempo=0;
    double angulo;
    short int direccion;
    short int nivel;

    //Daño que causa el proyectil
    short int daño;

    QTimer* timer;

public:
    Proyectil(short int _daño, double _angulo, double _v0, double xInicial, double yInicial, short int _direccion);
    Proyectil(short int _daño, double xInicial, double yInicial, short int _direccion);
    Proyectil(short int _nivel,short int _daño, double xInicial, double yInicial, short int _direccion);

    void colisionEnemiga();

private slots:
    void movimientoParabolico();
    void movimientoRectilineo();
    void movimientoCircular();
};

#endif // PROYECTIL_H

