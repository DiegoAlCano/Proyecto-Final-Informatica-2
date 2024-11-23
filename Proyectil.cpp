#include "Proyectil.h"


Proyectil::Proyectil(double xInicial, double yInicial, bool direccionDerecha, QObject* parent)
    : QObject(parent), x(xInicial), y(yInicial), gravedad(200), der(direccionDerecha) {

    setPixmap(QPixmap(":/Recursos/piedra.png"));
    setScale(0.04);

    vx = direccionDerecha ? velocidadHorizontal : -velocidadHorizontal;
    vy = 0;
    setPos(x, y);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Proyectil::actualizar);
    timer->start(16);
}

void Proyectil::actualizar() {
    double deltaTiempo = 0.016;

    x += vx * deltaTiempo;
    y += vy * deltaTiempo + 0.5 * gravedad * deltaTiempo * deltaTiempo;
    vy += gravedad * deltaTiempo;

    setPos(x, y);

    if (y > 500 or x < -50 or x > 670) {
        timer->stop();
        delete this;
        qDebug() << "bala eliminada";
    }
}
