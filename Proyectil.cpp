#include "Proyectil.h"
#include <QGraphicsScene>

#define PI 3.14159265

Proyectil::Proyectil(short _daño, double _angulo, double _v0, double xInicial, double yInicial, short int _direccion)
{

    setPixmap(QPixmap(":/Recursos/piedra.png"));
    setScale(0.04);

    daño = _daño;
    v0 = _v0;
    direccion = _direccion;
    angulo = _angulo * PI / 180; // Convertir ángulo a radianes
    x = xInicial;
    y = yInicial;

    // Velocidades iniciales
    vx = v0 * cos(angulo) * direccion;
    vy = -v0 * sin(angulo); // Negativo para que suba inicialmente

    setPos(x, y);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Proyectil::movimientoParabolico);
    timer->start(16);
}

Proyectil::Proyectil(short _daño, double xInicial, double yInicial, short _direccion)
{

    daño= _daño;
    x = xInicial;
    y = yInicial;
    direccion = _direccion;

    if(direccion==1){
        setPixmap(QPixmap(":/Recursos/Flecha.png"));
        setScale(0.7);
    }

    else{
        setPixmap(QPixmap(":/Recursos/FlechaIzquierda.png"));
        setScale(0.7);
    }

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Proyectil::movimientoRectilineo);
    timer->start(16);
}

void Proyectil::colisionEnemiga()
{
    QList<QGraphicsItem *> colisiones = collidingItems();
    for (QGraphicsItem *item : colisiones) {
        Enemigo *enemigo = dynamic_cast<Enemigo *>(item);
        if (enemigo) {
            enemigo->disminuirVida(daño);
            if (enemigo->getVida() == 0) {
                scene()->removeItem(enemigo);
                delete enemigo;
            }
            // Eliminar el proyectil después de colisionar
            timer->stop();
            scene()->removeItem(this);
            delete this;
            return;
        }
    }
}

void Proyectil::movimientoParabolico() {
    double deltaT = 0.016;

    // Actualizar velocidades
    vy += 9.8 * deltaT;

    // Actualizar posiciones
    x += vx * deltaT * 50;
    y += vy * deltaT * 50;

    QList<QGraphicsItem *> colisiones = collidingItems();
    for (QGraphicsItem *item : colisiones) {
        Enemigo *enemigo = dynamic_cast<Enemigo *>(item);
        if (enemigo) {
            enemigo->disminuirVida(daño);
            if (enemigo->getVida() == 0) {
                scene()->removeItem(enemigo);
                delete enemigo;
            }
            // Eliminar el proyectil después de colisionar
            timer->stop();
            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    // Establecer nueva posición
    setPos(x, y);

    if (y > 650 || x < -50 || x > 670) {
        timer->stop();
        scene()->removeItem(this);
        delete this;
    }
}


void Proyectil::movimientoRectilineo()
{
    x += (5.5*direccion);

    setPos(x,y);

    QList<QGraphicsItem *> colisiones = collidingItems();
    for (QGraphicsItem *item : colisiones) {
        Enemigo *enemigo = dynamic_cast<Enemigo *>(item);
        if (enemigo) {
            enemigo->disminuirVida(daño);
            if (enemigo->getVida() == 0) {
                scene()->removeItem(enemigo);
                delete enemigo;
            }
            // Eliminar el proyectil después de colisionar
            timer->stop();
            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    if (x < -30 || x > 670){
        timer->stop();
        scene()->removeItem(this);
        delete this;
    }

}
