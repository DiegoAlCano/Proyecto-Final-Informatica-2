#include "Heroe.h"
#include "QKeyEvent"
#include "QDebug"
#include "mainwindow.h"

Heroe::Heroe()
{
    hojaSprites.load(":/Recursos/SpriteHomeroCaminando.png");
    sprite = hojaSprites.copy(SpriteX,SpriteY,spriteAncho,spriteAlto);
    setPixmap(sprite);
}

void Heroe::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_A:
        movimiento(-7,0);
        confSprite(160);
        break;
    case Qt::Key_D:
        movimiento(7,0);
        confSprite(0);
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
    qDebug() << x;
    y += dy;
    setPos(x,y);
}

void Heroe::confSprite(int direccion)
{
    SpriteY = direccion;
    SpriteX = spriteAncho*contador;
    sprite = hojaSprites.copy(SpriteX,SpriteY,spriteAncho,spriteAlto);
    setPixmap(sprite);
    contador++;
    if(contador==8){
        contador = 0;
    }
}
