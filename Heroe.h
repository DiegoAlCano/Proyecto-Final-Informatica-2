#ifndef HEROE_H
#define HEROE_H

#include <QObject>
#include "QGraphicsPixmapItem"
#include "QPixmap"
#include "QKeyEvent"
#include "mainwindow.h"

class Heroe : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Heroe();
    void keyPressEvent(QKeyEvent *event);
    void movimiento(int dx, int dy);
    void confSprite(int direccion);
private:
    qreal x = 0;
    qreal y = 450;

    int SpriteX = 0;
    int SpriteY = 0;
    int spriteAncho = 150;
    int spriteAlto = 160;
    QPixmap hojaSprites;
    QPixmap sprite;
    int contador;
};

#endif // HEROE_H
