#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "Heroe.h"
#include "Personaje.h"
#include <QTimer>
#include "Proyectil.h"

class Enemigo : public Personaje
{
    Q_OBJECT
public:
    Enemigo(bool lado, int _SpriteX, int _SpriteY, int _spriteAncho, int _spriteAlto, int _daño, int _velocidad,short int y,short int _numSprites, const QString &rutaSprite);
    Enemigo(bool lado, int _SpriteX, int _SpriteY, int _spriteAncho, int _spriteAlto, int _daño, int _velocidad, int x1, int x2, int y, int _vida,short int _numSprites, const QString &rutaSprite);
    Enemigo(int _SpriteX, int _SpriteY, int _spriteAncho, int _spriteAlto, int _daño,short int _numSprites, const QString &rutaSprite);
    Enemigo(int _vida, int _SpriteX, int _SpriteY, int _spriteAncho, int _spriteAlto, int _daño, int _velocidad,short int _numSprites, const QString &rutaSprite);
    void moverHaciaHeroe();
    void moverSenoidal();
    void moverRapido();
    void mover();
    void iniciarSalto();
    void disminuirVida(int cantidadVida);

    unsigned short int getVida();


private:

    QTimer *moveTimer;

    int velocidad;
    int daño;
    int vida;
    short int numSprites;

    bool Pisado = false;
    bool colisionado = false;

    qreal velocidadY;

private slots:
    void iniciarMovimiento();
    void saltoMuerte();

signals:
    void enemigoEliminado(short int puntos);
};

#endif // ENEMIGO_H

