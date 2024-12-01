#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Personaje : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Personaje(unsigned short int _SpriteX, unsigned short int _SpriteY, unsigned short int _spriteAncho, unsigned short int _spriteAlto);
    void secuenciaSprite(short int direccion,unsigned short int maxContador);

protected:
    unsigned short int SpriteX;
    unsigned short int SpriteY;
    unsigned short int spriteAncho;
    unsigned short int spriteAlto;
    unsigned short int contador = 0;
    QPixmap hojaSprites;
    QPixmap sprite;
};

#endif // PERSONAJE_H
