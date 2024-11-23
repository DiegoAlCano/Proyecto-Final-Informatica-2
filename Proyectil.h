#ifndef PROYECTIL_H
#define PROYECTIL_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

class Proyectil : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

private:
    double x;
    double y;
    double vx;
    double vy;
    double gravedad;
    bool der;
    double velocidadHorizontal = 270.0;
    QTimer* timer;


public:
    Proyectil(double xInicial, double yInicial, bool direccionDerecha, QObject* parent = nullptr);

private slots:
    void actualizar();
signals:
};

#endif // PROYECTIL_H
