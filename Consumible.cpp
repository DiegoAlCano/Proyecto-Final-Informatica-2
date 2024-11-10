#include "Consumible.h"

Consumible::Consumible()
{
    setPixmap(QPixmap(":/Recursos/Dona.png")); // Cargar la imagen de la dona

    // Temporizador para el movimiento de la dona hacia abajo
    QTimer *fallTimer = new QTimer(this);
    connect(fallTimer, &QTimer::timeout, this, &Consumible::caida);
    fallTimer->start(50);  // Ajusta el intervalo para la velocidad de caída

}

void Consumible::caida()
{
    setPos(x(), y() + 15);  // Mover la dona hacia abajo

    // Verificar colisiones con otros elementos en la escena
    QList<QGraphicsItem *> collidingItemsList = collidingItems();
    for (QGraphicsItem *item : collidingItemsList) {
        // Verificar si el elemento con el que colisiona es el héroe
        if (dynamic_cast<Heroe *>(item)) {
            // Eliminar la dona de la escena
            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    // Eliminar la dona si sale de la pantalla (suponiendo un límite de 800px de altura)
    if (y() > 600) {
        scene()->removeItem(this);
        delete this;
    }
}
