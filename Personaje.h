#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Personaje : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Personaje(int _SpriteX, int _SpriteY, int _spriteAncho, int _spriteAlto);
    void secuenciaSprite(int direccion,int maxContador);

protected:
    int SpriteX;
    int SpriteY;
    int spriteAncho;
    int spriteAlto;
    int contador = 0;
    QPixmap hojaSprites;
    QPixmap sprite;
};

#endif // PERSONAJE_H
