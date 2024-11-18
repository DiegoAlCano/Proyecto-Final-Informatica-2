#include "Consumible.h"

Consumible::Consumible(const QString &rutaSprite, int _velocidadCaida, int _aumentoMunicion, int _aumentoVida)
{
    velocidadCaida = _velocidadCaida;
    aumentoMunicion = _aumentoMunicion;
    aumentoVida = _aumentoVida;

    setPixmap(QPixmap(rutaSprite)); // Cargar la imagen del consumible

    // Temporizador para el movimiento de la dona hacia abajo
    QTimer *fallTimer = new QTimer(this);
    connect(fallTimer, &QTimer::timeout, this, &Consumible::caida);
    fallTimer->start(50);  // Ajusta el intervalo para la velocidad de caída

}

void Consumible::caida()
{
    setPos(x(), y() + velocidadCaida);  // Mover la dona hacia abajo

    QList<QGraphicsItem *> collidingItemsList = collidingItems();
    for (QGraphicsItem *item : collidingItemsList) {
        // Verificar si el elemento con el que colisiona es el héroe
        Heroe *heroe = dynamic_cast<Heroe *>(item);
        if (heroe) {
            // Aumentar vida y munición del héroe
            heroe->aumentarVida(aumentoVida);
            heroe->aumentarMunicion(aumentoMunicion);
            heroe->aumentarScore(1);

            // Eliminar el consumible de la escena
            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    // Eliminar la dona si sale de la pantalla
    if (y() > 620) {
        scene()->removeItem(this);
        delete this;
        qDebug() <<"Dona eliminada";
    }
}
