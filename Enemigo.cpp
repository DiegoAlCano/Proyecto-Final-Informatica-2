#include "Enemigo.h"
#include "Heroe.h"
#include <QGraphicsScene>
#include "QDebug"

Enemigo::Enemigo(bool lado, int _SpriteX, int _SpriteY, int _spriteAncho, int _spriteAlto, const QString &rutaSprite)
    :Personaje(_SpriteX,_SpriteY,_spriteAncho,_spriteAlto)
{

    hojaSprites.load(rutaSprite);
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

    setPos(x()+velocidad,545);

    if(velocidad==5){
        secuenciaSprite(0,7);
    }
    else{
        secuenciaSprite(50,7);
    }


    // Verificar colisión con el héroe
    QList<QGraphicsItem *> collidingItemsList = collidingItems();
    for (QGraphicsItem *item : collidingItemsList) {
        Heroe *heroe = dynamic_cast<Heroe *>(item);
        if (heroe) {
            qreal posYHeroe = obtenerPosY(*heroe);
            qDebug()<<"Colision detectada: "<<posYHeroe;
            if (posYHeroe < 450) {
                qDebug()<<"HeroeY: "<< posYHeroe;
                qDebug() <<"Enemigo Eliminado: " << y();
                scene()->removeItem(this);
                delete this;
                return;
            }
            else{
                qDebug()<<"Mal: "<<posYHeroe;
                heroe->disminuirVida(10);
            }
        }
    }

    // Si el enemigo sale de los límites de la escena, se elimina

    if (x() < -70|| x() > 650) {
        scene()->removeItem(this);
        delete this;
        qDebug()<<"Enemigo Eliminado";
    }
}

