#include "Heroe.h"
#include "QKeyEvent"
#include "QDebug"
#include "mainwindow.h"
#include "QGraphicsTextItem"

Heroe::Heroe(char _nivel, qreal _y, int _SpriteX, int _SpriteY, int _spriteAncho, int _spriteAlto, int _vida, int _municion, const QString &rutaSprite)
    :Personaje(_SpriteX,_SpriteY,_spriteAncho,_spriteAlto)
{
    nivel = _nivel;
    vida = _vida;
    municion = _municion;
    y = _y;
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
            if(nivel=='2' or nivel=='1'){
                if(direccionHeroe==1){
                    Proyectil *proyectil = new Proyectil(10,30,7.5,x+90,y+50,direccionHeroe);
                    scene()->addItem(proyectil);
                }
                else{
                    Proyectil *proyectil = new Proyectil(10,30,7.5,x-20,y+50,direccionHeroe);
                    scene()->addItem(proyectil);
                }
            }
            else if(nivel=='3'){
                if(direccionHeroe==1){
                    Proyectil *proyectil = new Proyectil(10,x+90,y+42,direccionHeroe);
                    scene()->addItem(proyectil);
                }
                else{
                    Proyectil *proyectil = new Proyectil(10,x-20,y+42,direccionHeroe);
                    scene()->addItem(proyectil);
                }
            }
            else if(nivel=='4'){
                if(direccionHeroe==1){
                    Proyectil *proyectil = new Proyectil('4',10,x+90,y+42,direccionHeroe);
                    scene()->addItem(proyectil);
                }
                else{
                    Proyectil *proyectil = new Proyectil('4',10,x-20,y+42,direccionHeroe);
                    scene()->addItem(proyectil);
                }
            }

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

    if(nivel=='1' or nivel=='3' or nivel == '4'){
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
    }

    else{
        if (x > 530){
            x = 530;
        }
        else if(x < 90){
            x=90;
        }
        if(y == 130) {
            y = 130;
            enElAire = false;
            enCaida =  false;
            velocidadX = 0;
            saltoTimer->stop();

            if(direccionHeroe==1){
                secuenciaSprite(0,8);
            }

            else{
                secuenciaSprite(160,8);
            }
        }
    }
    setPos(x, y);
//    secuenciaSprite(640,8);
//    qDebug() <<"X: "<< x<<"Y: "<< y;

}


void Heroe::movimiento(int dx, int dy) {

    if(nivel=='1' or nivel=='3' or nivel== '4'){
        if (x > 555) {
            x = 555;
        }

        else if (x < -55) {
            x = -55;
        }
    }

    else{
        if(x > 530) {
            x = 530;
        }

        else if (x < 90) {
            x =90;
        }
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

    if(municion>=15){
        municion = 15;
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

    qDebug()<<"Golpe";

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

unsigned short Heroe::getMunicion()
{
    return municion;
}

qreal Heroe::getPosX()
{
    return x;
}

void Heroe::setNivel(char _Nivel)
{
    nivel = _Nivel;
}

void Heroe::disparar(int direccion)
{

    disminuirMunicion();

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

