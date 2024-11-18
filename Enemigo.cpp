#include "Enemigo.h"
#include "Heroe.h"
#include <QGraphicsScene>
#include "QDebug"

Enemigo::Enemigo(bool lado, int _SpriteX, int _SpriteY, int _spriteAncho, int _spriteAlto, int _daño, int _velocidad, const QString &rutaSprite)
    :Personaje(_SpriteX,_SpriteY,_spriteAncho,_spriteAlto)
{
    daño = _daño;

    hojaSprites.load(rutaSprite);
    sprite = hojaSprites.copy(SpriteX,SpriteY,spriteAncho,spriteAlto);
    setPixmap(sprite);

    if (lado) {
        setPos(-20,505);
        velocidad = _velocidad;
    } else {
        setPos(540,505);
        velocidad = _velocidad*(-1);
    }

    // Temporizador para mover al enemigo
    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &Enemigo::moverHaciaHeroe);
    moveTimer->start(50);

}

void Enemigo::moverHaciaHeroe() {
    setPos(x() + velocidad, y());

    if (velocidad>0 ) {
        secuenciaSprite(0, 7);
    }
    else {
        secuenciaSprite(125, 7);
    }

    // Verificar colisión con el héroe
    QList<QGraphicsItem *> collidingItemsList = collidingItems();
    for (QGraphicsItem *item : collidingItemsList) {
        Heroe *heroe = dynamic_cast<Heroe *>(item);
        if (heroe and !Pisado) {  // Verificar que el enemigo no esté ya en desplazamiento

            bool cayendo = heroe->get_enCaida();

            if (cayendo) {
                heroe->aumentarVida(5);
                iniciarDesplazamientoHaciaAbajo();  // Inicia el salto del enemigo antes de eliminarlo
            }
            else if(!colisionado) {
                colisionado = true;
                heroe->disminuirVida(daño);  // Aplica daño solo si el enemigo no está en desplazamiento
                qDebug()<<"Enemigo y: "<<y();
            }
        }
    }

    // Si el enemigo sale de los límites de la escena, se elimina
    if (x() < -70 || x() > 650) {
        scene()->removeItem(this);
        delete this;
        qDebug() << "Enemigo Eliminado";
    }
}

void Enemigo::iniciarDesplazamientoHaciaAbajo() {
    Pisado = true;  // Activar indicador de desplazamiento
    velocidadY = -15;  // Impulso inicial hacia arriba al ser pisado

    // Configurar un temporizador para hacer el salto y caída
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Enemigo::saltoMuerte);
    timer->start(50);  // Ajusta el intervalo del temporizador para la caída gradual
}

void Enemigo::saltoMuerte() {
    velocidadY += 2;  // Aumentar la velocidadY para simular la gravedad
    setPos(x(), y() + velocidadY);

    // Si el enemigo sale de la pantalla, se elimina
    if (y() > 620) {
        scene()->removeItem(this);
        delete this;
        qDebug() << "Enemigo Eliminado";
    }
}
