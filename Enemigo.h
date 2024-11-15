#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "Heroe.h"
#include "Personaje.h"
#include <QTimer>

class Enemigo : public Personaje
{
    Q_OBJECT
public:
    Enemigo(bool lado, int _SpriteX, int _SpriteY, int _spriteAncho, int _spriteAlto, const QString &rutaSprite);
    void moverHaciaHeroe();
private:

    QTimer *moveTimer;
    int velocidad;

};

#endif // ENEMIGO_H
