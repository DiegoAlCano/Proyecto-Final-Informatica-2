#include "Enemigo.h"
#include "Heroe.h"
#include <QGraphicsScene>
#include "QDebug"
#include <cmath>

Enemigo::Enemigo(bool lado, int _SpriteX, int _SpriteY, int _spriteAncho, int _spriteAlto, unsigned short _daño, short _velocidad, short y, short _numSprites, const QString &rutaSprite)
    :Personaje(_SpriteX,_SpriteY,_spriteAncho,_spriteAlto)
{
    daño = _daño;
    numSprites = _numSprites;

    hojaSprites.load(rutaSprite);
    sprite = hojaSprites.copy(SpriteX,SpriteY,spriteAncho,spriteAlto);
    setPixmap(sprite);

    if (lado) {
        setPos(-20,y);
        velocidad = _velocidad;
    } else {
        setPos(540,y);
        velocidad = _velocidad*(-1);
    }

    // Temporizador para mover al enemigo
    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &Enemigo::moverHaciaHeroe);
    moveTimer->start(50);

}


Enemigo::Enemigo(bool lado, int _SpriteX, int _SpriteY, int _spriteAncho, int _spriteAlto, unsigned short _daño, short _velocidad, short x1, short x2, short y, unsigned short _vida, short _numSprites, const QString &rutaSprite)
    :Personaje(_SpriteX,_SpriteY,_spriteAncho,_spriteAlto)
{
    daño = _daño;
    vida = _vida;
    numSprites = _numSprites;

    hojaSprites.load(rutaSprite);
    sprite = hojaSprites.copy(SpriteX,SpriteY,spriteAncho,spriteAlto);
    setPixmap(sprite);

    if (lado) {
        setPos(x1,y);
        velocidad = _velocidad;
    } else {
        setPos(x2,y);
        velocidad = _velocidad*(-1);
    }

    // Temporizador para mover al enemigo
    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &Enemigo::mover);
    moveTimer->start(50);
}


Enemigo::Enemigo(unsigned short _vida,int _SpriteX, int _SpriteY, int _spriteAncho, int _spriteAlto, unsigned short _daño, short _numSprites, const QString &rutaSprite)
    :Personaje(_SpriteX,_SpriteY,_spriteAncho,_spriteAlto)
{
    daño = _daño;
    numSprites = _numSprites;
    vida = _vida;

    hojaSprites.load(rutaSprite);
    sprite = hojaSprites.copy(SpriteX,SpriteY,spriteAncho,spriteAlto);
    setPixmap(sprite);

    setPos(-100,y());

    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &Enemigo::moverSenoidal);
    moveTimer->start(50);

}

Enemigo::Enemigo(const QString &rutaSprite,int time, unsigned short _vida, int _SpriteX, int _SpriteY, int _spriteAncho, int _spriteAlto, unsigned short _daño, short _velocidad, short _numSprites)
        :Personaje(_SpriteX,_SpriteY,_spriteAncho,_spriteAlto)
{
    daño = _daño;
    vida = _vida;
    velocidad = _velocidad;
    numSprites = _numSprites;
    moveTimer = nullptr;
    colisionado = false;

    hojaSprites.load(rutaSprite);
    sprite = hojaSprites.copy(SpriteX,SpriteY,spriteAncho,spriteAlto);
    setPixmap(sprite);

    // Temporizador para activar el movimiento cada 15 segundos
    QTimer *activadorMovimiento = new QTimer(this);
    connect(activadorMovimiento, &QTimer::timeout, this, [this]() {
        iniciarMovimiento();
    });
    activadorMovimiento->start(time);

}

Enemigo::Enemigo(short randomX, int _SpriteX, int _SpriteY, int _spriteAncho, int _spriteAlto, unsigned short _daño, short _numSprites)
        :Personaje(_SpriteX,_SpriteY,_spriteAncho,_spriteAlto)
{
    daño = _daño;
    numSprites = _numSprites;

    hojaSprites.load(":/Recursos/manos.png");
    sprite = hojaSprites.copy(SpriteX,SpriteY,spriteAncho,spriteAlto);
    setPixmap(sprite);

    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, [=]() {
        salirSuelo(randomX);
    });
    moveTimer->start(100);
}

void Enemigo::moverHaciaHeroe() {
    setPos(x() + velocidad, y());

    if (velocidad>0 ) {
        secuenciaSprite(0, numSprites);
    }
    else {
        secuenciaSprite(spriteAlto, numSprites);
    }

    // Verificar colisión con el héroe
    QList<QGraphicsItem *> collidingItemsList = collidingItems();
    for (QGraphicsItem *item : collidingItemsList) {
        Heroe *heroe = dynamic_cast<Heroe *>(item);
        if (heroe and !Pisado) {

            bool cayendo = heroe->get_enCaida();

            if (cayendo) {
                heroe->aumentarVida(10);
                iniciarSalto();
            }
            else if(!colisionado) {
                colisionado = true;
                heroe->disminuirVida(daño);  // Aplica daño solo si el enemigo no está en desplazamiento
            }
        }
    }

    // Si el enemigo sale de los límites de la escena, se elimina
    if (x() < -70 || x() > 650) {
        scene()->removeItem(this);
        delete this;
    }
}

void Enemigo::moverSenoidal()
{
    // Calcular nueva posición en Y usando movimiento senoidal
    int nuevaPosY = 100 * qSin((x() * M_PI) / 180) + 355;
    setPos(x() + 8, nuevaPosY);  // Avanza en X y ajusta la posición en Y

    // Cambia la secuencia del sprite
    secuenciaSprite(0, numSprites);

    // Si el enemigo supera el límite derecho de la escena, se elimina
    if (x() > 650) {
        scene()->removeItem(this);
        delete this;
        return;
    }

    // Verificar colisión con el héroe
    Heroe *heroe = nullptr;
    for (QGraphicsItem *item : scene()->items()) {
        heroe = dynamic_cast<Heroe*>(item);
        if (heroe){
            break;
        }
    }

    if (heroe and !colisionado and collidesWithItem(heroe)) {
        colisionado = true;
        heroe->disminuirVida(daño);
    }
}

void Enemigo::iniciarMovimiento() {
    if (moveTimer == nullptr) { // Solo crea un temporizador si no existe
        moveTimer = new QTimer(this);
        connect(moveTimer, &QTimer::timeout, this, &Enemigo::moverRapido);
        moveTimer->start(50);
    }
}

void Enemigo::moverRapido()
{
    static bool moviendoIzquierda = true; // Bandera para controlar la dirección del movimiento

    // Detectar colisión con el héroe
    QList<QGraphicsItem *> colisiones = collidingItems();
    for (QGraphicsItem *item : colisiones) {
        Heroe *heroe = dynamic_cast<Heroe *>(item);
        if (heroe) {
            // Reducir la vida del héroe solo si no ha colisionado aún en esta dirección
            if (!colisionado) {
                colisionado = true;
                heroe->disminuirVida(daño);
                break;
            }
        }
    }

    if (moviendoIzquierda) {
        // Mover hacia la izquierda
        setPos(x() - velocidad, y());
        secuenciaSprite(spriteAlto, numSprites);

        if (x() <= 3) {
            moviendoIzquierda = false; // Cambiar dirección al llegar a -10
            colisionado = false; // Permitir colisión en la nueva dirección
        }
    }
    else {
        // Mover hacia la derecha
        setPos(x() + velocidad, y());
        secuenciaSprite(0, numSprites);

        if (x() >= 530) {
            secuenciaSprite(spriteAlto, numSprites);
            moveTimer->stop();
            moveTimer->deleteLater(); // Limpiar el temporizador
            moveTimer = nullptr;
            moviendoIzquierda = true; // Cambiar dirección
            colisionado = false; // Permitir colisión en la nueva dirección
        }
    }
}

void Enemigo::mover()
{
    setPos(x() + velocidad,y());

    if (velocidad>0 ) {
        secuenciaSprite(0, numSprites);
    }
    else {
        secuenciaSprite(spriteAlto, numSprites);
    }

    QList<QGraphicsItem *> colisiones = collidingItems();
    for (QGraphicsItem *item : colisiones) {
        Heroe *heroe = dynamic_cast<Heroe *>(item);
        if (heroe) {
            if(!colisionado){
                heroe->disminuirVida(daño);
            }
            colisionado = true;
        }
    }

    // Eliminar el enemigo si sale de la escena
    if (x() < -50 || x() > scene()->width() + 50) {
        scene()->removeItem(this);
        delete this;
    }
}

void Enemigo::salirSuelo(short randomX)
{
    setPos(randomX,420);

    secuenciaSprite(0,numSprites);

    QTimer *timerEliminar = new QTimer(this);
    connect(timerEliminar, &QTimer::timeout, this, [=]() {
        scene()->removeItem(this);
        delete this;
    });
    timerEliminar->start(1000);

    QList<QGraphicsItem *> colisiones = collidingItems();
    for (QGraphicsItem *item : colisiones) {
        Heroe *heroe = dynamic_cast<Heroe *>(item);
        if (heroe) {
            if(!colisionado){
                heroe->disminuirVida(daño);
            }
            colisionado = true;
        }
    }

}


void Enemigo::iniciarSalto() {
    Pisado = true;  // Activar indicador de desplazamiento
    velocidadY = -15;  // Impulso inicial hacia arriba al ser pisado

    // Configurar un temporizador para hacer el salto y caída
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Enemigo::saltoMuerte);
    timer->start(50);  // Ajusta el intervalo del temporizador para la caída gradual
}

void Enemigo::disminuirVida(int cantidadVida)
{
    vida -= cantidadVida;
    if(vida<=0){
        vida = 0;
        emit enemigoEliminado(1);
    }
}

unsigned short Enemigo::getVida()
{
    return vida;
}

int Enemigo::getX()
{
    return x();
}

void Enemigo::saltoMuerte() {
    velocidadY += 2;  // Aumentar la velocidadY para simular la gravedad
    setPos(x(), y() + velocidadY);

    // Si el enemigo sale de la pantalla, se elimina
    if (y() > 620) {
        scene()->removeItem(this);
        delete this;
    }
}
