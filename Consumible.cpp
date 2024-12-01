#include "Consumible.h"

Consumible::Consumible(const QString &rutaSprite, unsigned short _velocidadCaida, unsigned short _aumentoMunicion, unsigned short _aumentoVida)
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

void Consumible::setAumentoVida(unsigned short _aumentoVida)
{
    aumentoVida = _aumentoVida;
}

void Consumible::setaumentoMunicion(unsigned short _aumentoMunicion)
{
    aumentoMunicion = _aumentoMunicion;
}

void Consumible::caida()
{
    setPos(x(), y() + velocidadCaida);  // Mover la dona hacia abajo

    // Verificar si colisiona con el héroe
    QList<QGraphicsItem *> collidingItemsList = collidingItems();
    for (QGraphicsItem *item : collidingItemsList) {
        Heroe *heroe = dynamic_cast<Heroe *>(item);
        if (heroe) {
            // Aumentar vida y munición del héroe
            if (aumentoMunicion == 0 and aumentoVida == 0) {
                heroe->aumentarScore(1);
            } else {
                heroe->aumentarVida(aumentoVida);
                heroe->aumentarMunicion(aumentoMunicion);
            }

            // Eliminar el consumible de la escena
            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    // Eliminar la dona si sale de la pantalla
    if (y() > scene()->height()) {
        scene()->removeItem(this);
        delete this;
    }
}
