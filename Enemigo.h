#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "Heroe.h"
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Enemigo : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Enemigo(bool lado);
    void moverHaciaHeroe();
    void Enemigo_confSprite(int direccion);
private:

    int Enemigo_SpriteX = 0;
    int Enemigo_SpriteY = 0;
    int Enemigo_spriteAncho = 100;
    int Enemigo_spriteAlto = 50;
    QPixmap Enemigo_hojaSprites;
    QPixmap Enemigo_sprite;
    int Enemigo_contador;

    QTimer *moveTimer;
    int velocidad;
};

#endif // ENEMIGO_H
