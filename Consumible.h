#ifndef CONSUMIBLE_H
#define CONSUMIBLE_H

#include "Heroe.h"
#include "mainwindow.h"
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Consumible : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Consumible(const QString &rutaSprite,unsigned short int _velocidadCaida,unsigned short int _aumentoMunicion,unsigned short int _aumentoVida);

    void setAumentoVida(unsigned short int _aumentoVida);
    void setaumentoMunicion(unsigned short int _aumentoMunicion);
private:
    unsigned short int velocidadCaida;
    unsigned short int aumentoMunicion;
    unsigned short int aumentoVida;
public slots:
    void caida();
};

#endif // CONSUMIBLE_H


