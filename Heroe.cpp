#include "Heroe.h"
#include "QKeyEvent"
#include "QDebug"
#include "mainwindow.h"

Heroe::Heroe(int _SpriteX, int _SpriteY, int _spriteAncho, int _spriteAlto, std::string rutaSprite)
    :Personaje(_SpriteX,_SpriteY,_spriteAncho,_spriteAlto)
{
    hojaSprites.load(QString::fromStdString(rutaSprite));
    sprite = hojaSprites.copy(SpriteX,SpriteY,spriteAncho,spriteAlto);
    setPixmap(sprite);
}

void Heroe::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_A:
        movimiento(-6,0);
        secuenciaSprite(160,8);
        break;
    case Qt::Key_D:
        movimiento(6,0);
        secuenciaSprite(0,8);
        break;
    default:
        break;
    }
}

void Heroe::movimiento(int dx, int dy)
{
    if(x>540){
        x=540;
    }

    else if(x<-38){
        x=-38;
    }
    x += dx;
    y += dy;
    setPos(x,y);
}
