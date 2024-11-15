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
//    void disparar(int direccion);
    friend qreal obtenerPosY(const Heroe &heroe);
    friend bool obtenerenElAire(const Heroe &heroe);

private slots:
    void actualizarSalto();  

private:

    qreal x = 0;
    qreal y = 450;
    int vida;
    int municion;

    // Texto para mostrar la vida en la escena
    QGraphicsTextItem *infoVida = nullptr;

    qreal velocidadY = 0;  // Velocidad vertical para el salto
    qreal velocidadX;
    int direccionHeroe;
    bool enElAire = false; // Indica si el héroe está en el aire

    QTimer *saltoTimer;    // Temporizador para controlar el salto
};

#endif // HEROE_H
