#ifndef HEROE_H
#define HEROE_H

#include "Personaje.h"
#include "QKeyEvent"
#include "mainwindow.h"
#include "QGraphicsTextItem"

class Heroe : public Personaje
{
    Q_OBJECT
public:
    Heroe(int _SpriteX, int _SpriteY, int _spriteAncho, int _spriteAlto, int _vida, int _municion, const QString &rutaSprite);
    void keyPressEvent(QKeyEvent *event);
    void movimiento(int dx, int dy);
    void aumentarVida(int cantidadVida);
    void aumentarMunicion(int cantidadMunicion);
    void disminuirVida(int cantidadVida);
    void disminuirMunicion();
    void mostrarInformacion();
    void aumentarScore(int aumentoScore);

    short int getVida();
    bool get_enCaida();
    unsigned short int getScore();
    friend qreal obtenerPosY(const Heroe &heroe);
    friend bool obtenerenElAire(const Heroe &heroe);

private slots:
    void actualizarSalto();

private:

    //posicion
    qreal x = 0;
    qreal y = 450;

    //Especificaciones
    short int vida;
    unsigned short int municion;
    unsigned short int score;

    //atributos para el salto
    qreal velocidadY = 0;
    qreal velocidadX;
    int direccionHeroe;
    bool enElAire = false;
    bool enCaida = false;
    QTimer *saltoTimer;    // Temporizador para controlar el salto
};

#endif // HEROE_H
