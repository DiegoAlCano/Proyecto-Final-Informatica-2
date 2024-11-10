#include "Enemigo.h"
#include <QGraphicsScene>
#include "QDebug"

Enemigo::Enemigo(bool lado)
{
    Enemigo_hojaSprites.load(":/Recursos/Enemigo1.png");
    Enemigo_sprite = Enemigo_hojaSprites.copy(Enemigo_SpriteX,Enemigo_SpriteY,Enemigo_spriteAncho,Enemigo_spriteAlto);
    setPixmap(Enemigo_sprite);

    if (lado) {
        setPos(0,560);
        velocidad = 5;
    } else {
        setPos(540,560);
        velocidad = -5;
    }

    // Temporizador para mover al enemigo
    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &Enemigo::moverHaciaHeroe);
    moveTimer->start(50);

}

void Enemigo::moverHaciaHeroe() {

    setPos(x()+velocidad,560);


    if(velocidad==5){
        Enemigo_confSprite(0);
    }
    else{
        Enemigo_confSprite(50);
    }


    /*
    // Verificar colisión con el héroe
    QList<QGraphicsItem *> collidingItemsList = collidingItems();
    for (QGraphicsItem *item : collidingItemsList) {
        if (dynamic_cast<Heroe *>(item)) {
            // Si el enemigo golpea al héroe, se elimina el enemigo
            scene()->removeItem(this);
            delete this;
            return;
        }
    }
    */

    // Si el enemigo sale de los límites de la escena, se elimina
    if (x() < -50|| x() > 570) {  // Ajusta estos límites según el ancho de tu escena
        scene()->removeItem(this);
        delete this;
    }

}

void Enemigo::Enemigo_confSprite(int direccion)
{
    Enemigo_SpriteY = direccion;
    Enemigo_SpriteX = Enemigo_spriteAncho*Enemigo_contador;
    Enemigo_sprite = Enemigo_hojaSprites.copy(Enemigo_SpriteX,Enemigo_SpriteY,Enemigo_spriteAncho,Enemigo_spriteAlto);
    setPixmap(Enemigo_sprite);
    Enemigo_contador++;
    if(Enemigo_contador==7){
        Enemigo_contador = 0;
    }
}
