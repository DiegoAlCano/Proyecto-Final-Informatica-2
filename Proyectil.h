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

    //Daño que causa el proyectil
    short int daño;

    QTimer* timer;


public:
    Proyectil(short int _daño, double _angulo, double _v0, double xInicial, double yInicial, short int _direccion);
    Proyectil(short int _daño, double xInicial, double yInicial, short int _direccion);

private slots:
    void movimientoParabolico();
    void movimientoRectilineo();
};

#endif // PROYECTIL_H
