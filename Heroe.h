#ifndef HEROE_H
#define HEROE_H

#include "Personaje.h"
#include "QKeyEvent"
#include "mainwindow.h"

class Heroe : public Personaje
{
    Q_OBJECT
public:
    Heroe(int _SpriteX, int _SpriteY, int _spriteAncho, int _spriteAlto,std::string rutaSprite);
    void keyPressEvent(QKeyEvent *event);
    void movimiento(int dx, int dy);
private:

    qreal x = 0;
    qreal y = 450;
};

#endif // HEROE_H
