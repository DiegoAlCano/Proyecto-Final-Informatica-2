#include "Heroe.h"
#include "QKeyEvent"
#include "QDebug"
#include "mainwindow.h"
#include "QGraphicsTextItem"

Heroe::Heroe(int _SpriteX, int _SpriteY, int _spriteAncho, int _spriteAlto, int _vida, int _municion, const QString &rutaSprite)
    :Personaje(_SpriteX,_SpriteY,_spriteAncho,_spriteAlto)
{
    vida = _vida;
    municion = _municion;
    hojaSprites.load(rutaSprite);
    sprite = hojaSprites.copy(SpriteX,SpriteY,spriteAncho,spriteAlto);
    setPixmap(sprite);
    saltoTimer = new QTimer(this);
    connect(saltoTimer, &QTimer::timeout, this, &Heroe::actualizarSalto);
}

void Heroe::keyPressEvent(QKeyEvent *event) {

    switch (event->key()) {
    case Qt::Key_A:
        if (!enElAire) {
            direccionHeroe = -1;
            movimiento(-6, 0);        // Movimiento en el suelo
            secuenciaSprite(160, 8);
        }
        break;
    case Qt::Key_D:
        if (!enElAire) {
            direccionHeroe = 1;
            movimiento(6, 0);         // Movimiento en el suelo
            secuenciaSprite(0, 8);
        }
        break;
    case Qt::Key_W:

        if(direccionHeroe==1){
            secuenciaSprite(640,8);
        }

        else{
            secuenciaSprite(800,8);
        }

        if (!enElAire) {               // Inicia el salto solo si el héroe está en el suelo
            velocidadY = -15;           // Velocidad inicial hacia arriba
            velocidadX = 5*direccionHeroe;
            enElAire = true;
            saltoTimer->start(30);      // Inicia el temporizador para el salto
            if(direccionHeroe==1){
                secuenciaSprite(640,8);
            }

            else{
                secuenciaSprite(800,8);
            }
        }
        break;
    case Qt::Key_P:
        if(municion>0){
            disparar(direccionHeroe);
        }
        break;
    default:
        break;
    }
}

void Heroe::actualizarSalto() {

    velocidadY += 1;

    x += velocidadX;

    y += velocidadY;

    if(velocidadY>=0){
        enCaida = true;
    }

    // Limita las posiciones
    if (x > 555) {
        x = 555;
    }

    else if (x < -55) {
        x = -55;
    }

    // Si el héroe alcanza el suelo, detiene el salto
    if (y == 450) {
        y = 450;
        enElAire = false;
        enCaida = false;
        velocidadX = 0;  // Detiene el movimiento horizontal cuando aterriza
        saltoTimer->stop();

        if(direccionHeroe==1){
            secuenciaSprite(0,8);
        }

        else{
            secuenciaSprite(160,8);
        }

    }

    setPos(x, y);
//    secuenciaSprite(640,8);
//    qDebug() <<"X: "<< x<<"Y: "<< y;

}


void Heroe::movimiento(int dx, int dy) {

    if (x > 555) {
        x = 555;
    }

    else if (x < -55) {
        x = -55;
    }
    x += dx;
    y += dy;
    setPos(x, y);

}

void Heroe::aumentarVida(int cantidadVida)
{
    vida += cantidadVida;
    if(vida>100){
        vida = 100;
    }
}

void Heroe::aumentarMunicion(int cantidadMunicion)
{
    municion += cantidadMunicion;

    if(municion>=12){
        municion = 12;
    }

}

void Heroe::disminuirVida(int cantidadVida)
{
    vida -= cantidadVida;

    if(vida<=0){
        vida = 0;
    }

    if(direccionHeroe ==1){
        secuenciaSprite(320,8);
    }
    else{
        secuenciaSprite(480,8);
    }

}

void Heroe::disminuirMunicion()
{
    municion -= 1;

    if(municion<=0){
        municion = 0;
    }
}

void Heroe::aumentarScore(int aumentoScore)
{
    score = score+aumentoScore;
}

short int Heroe::getVida()
{
    return vida;
}

bool Heroe::get_enCaida()
{
    return enCaida;
}

unsigned short Heroe::getScore()
{
    return score;
}

qreal Heroe::getPosX()
{
    return x;
}


void Heroe::disparar(int direccion)
{

    setPos(x,y);

    if(direccion==1){
        secuenciaSprite(960,8);
    }

    else{
        secuenciaSprite(1120,8);
    }
}

void Heroe::modificarPosX(qreal newX)
{
    x = newX;
}

qreal obtenerPosY(const Heroe &heroe) {
    return heroe.y;
}

bool obtenerenElAire(const Heroe &heroe){
    return heroe.enElAire;
}
    
