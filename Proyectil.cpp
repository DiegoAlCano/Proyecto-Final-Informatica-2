#include "Proyectil.h"
#include <QGraphicsScene>

#define PI 3.14159265

Proyectil::Proyectil(short _daño, double _angulo, double _v0, double xInicial, double yInicial, short int _direccion)
{
    // Configuración inicial del proyectil
    setPixmap(QPixmap(":/Recursos/piedra.png"));
    setScale(0.04);

    daño = _daño;

    // Inicialización de variables
    v0 = _v0;
    direccion = _direccion;
    angulo = _angulo * PI / 180; // Convertir ángulo a radianes
    x = xInicial;
    y = yInicial;

    // Velocidades iniciales
    vx = v0 * cos(angulo) * direccion;
    vy = -v0 * sin(angulo); // Negativo para que suba inicialmente

    setPos(x, y);

    // Configuración del temporizador
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Proyectil::movimientoParabolico);
    timer->start(16); // Intervalo de 32 ms
}

void Proyectil::movimientoParabolico() {
    double deltaT = 0.016;

    // Actualizar velocidades
    vy += 9.8 * deltaT;

    // Actualizar posiciones
    x += vx * deltaT * 50;
    y += vy * deltaT * 50;

    // Establecer nueva posición
    setPos(x, y);

    // Detectar colisiones
    QList<QGraphicsItem *> colisiones = collidingItems();
    for (QGraphicsItem *item : colisiones) {
        Enemigo *enemigo = dynamic_cast<Enemigo *>(item);
        if (enemigo) {
            enemigo->disminuirVida(daño);
            if(enemigo->getVida()==0){
                scene()->removeItem(enemigo);
                delete enemigo;

            }
            // Eliminar el proyectil después de colisionar
            timer->stop();
            scene()->removeItem(this);
            delete this;
            return; // Salir de la función para evitar problemas tras la eliminación
        }
    }

    // Verificar si el proyectil sale de los límites
    if (y > 650 || x < -50 || x > 670) {
        timer->stop();
        scene()->removeItem(this);
        delete this;
        qDebug() << "Proyectil eliminado";
    }
}
