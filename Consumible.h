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
    Consumible(const QString &rutaSprite, int _velocidadCaida, int _aumentoMunicion, int _aumentoVida);
private:
    int velocidadCaida;
    int aumentoMunicion;
    int aumentoVida;
public slots:
    void caida();
};

#endif // CONSUMIBLE_H

