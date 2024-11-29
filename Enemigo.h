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
    Enemigo(bool lado, int _SpriteX, int _SpriteY, int _spriteAncho, int _spriteAlto,unsigned short int _daño,short int _velocidad,short int y,short int _numSprites, const QString &rutaSprite);
    Enemigo(bool lado, int _SpriteX, int _SpriteY, int _spriteAncho, int _spriteAlto, unsigned short int _daño, short int _velocidad,short int x1,short int x2,short int y, unsigned short int _vida,short int _numSprites, const QString &rutaSprite);
    Enemigo(unsigned short int _vida,int _SpriteX, int _SpriteY, int _spriteAncho, int _spriteAlto,unsigned short int  _daño,short int _numSprites, const QString &rutaSprite);
    Enemigo(unsigned short int _vida, int _SpriteX, int _SpriteY, int _spriteAncho, int _spriteAlto, unsigned short int _daño, short int _velocidad,short int _numSprites, const QString &rutaSprite);
    Enemigo(short int randomX,int _SpriteX, int _SpriteY, int _spriteAncho, int _spriteAlto, unsigned short int _daño,short int _numSprites);

    void moverHaciaHeroe();
    void moverSenoidal();
    void moverRapido();
    void mover();
    void salirSuelo(short int randomX);
    void iniciarSalto();
    void disminuirVida(int cantidadVida);

    unsigned short int getVida();


private:

    QTimer *moveTimer;

    short int velocidad;
    unsigned short int daño;
    unsigned short int vida;
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
