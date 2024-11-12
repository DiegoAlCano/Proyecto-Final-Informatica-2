#include "Enemigo.h"
#include <QGraphicsScene>
#include "QDebug"

Enemigo::Enemigo(bool lado, int _SpriteX, int _SpriteY, int _spriteAncho, int _spriteAlto, std::string rutaSprite)
    :Personaje(_SpriteX,_SpriteY,_spriteAncho,_spriteAlto)
{
    hojaSprites.load(QString::fromStdString(rutaSprite));
    sprite = hojaSprites.copy(SpriteX,SpriteY,spriteAncho,spriteAlto);
    setPixmap(sprite);

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
        secuenciaSprite(0,7);
    }
    else{
        secuenciaSprite(50,7);
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
    if (x() < -50|| x() > 600) {  // Ajusta estos límites según el ancho de tu escena
        scene()->removeItem(this);
        delete this;
    }

}
