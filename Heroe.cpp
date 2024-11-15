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
        if (!enElAire) {               // Inicia el salto solo si el héroe está en el suelo
            velocidadY = -15;           // Velocidad inicial hacia arriba
            velocidadX = 5*direccionHeroe;             
            enElAire = true;
            saltoTimer->start(30);      // Inicia el temporizador para el salto
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

    // Limita las posiciones
    if (x > 555) {
        x = 555;
    } else if (x < -55) {
        x = -55;
    }

    // Si el héroe alcanza el suelo, detiene el salto
    if (y == 450) {
        y = 450;
        enElAire = false;
        velocidadX = 0;  // Detiene el movimiento horizontal cuando aterriza
        saltoTimer->stop();
    }

    setPos(x, y);
//    qDebug() <<"X: "<< x<<"Y: "<< y;

}


void Heroe::movimiento(int dx, int dy) {

    if (x > 555) {
        x = 555;
    } else if (x < -55) {
        x = -55;
    }
    x += dx;
    y += dy;
    setPos(x, y);
//    qDebug() << "x: " << x;
//    qDebug() << "y: " << y;
}

void Heroe::aumentarVida(int cantidadVida)
{
    vida += cantidadVida;
    if(vida>100){
        vida = 100;
    }
    mostrarInformacion();
}

void Heroe::aumentarMunicion(int cantidadMunicion)
{
    municion += cantidadMunicion;

}

void Heroe::disminuirVida(int cantidadVida)
{
    vida -= cantidadVida;
    mostrarInformacion();

}

void Heroe::disminuirMunicion()
{
    municion -= 1;
}

void Heroe::mostrarInformacion()
{
    // Si el texto ya existe, actualiza su contenido
    if (infoVida) {
        infoVida->setPlainText(QString("vida: %1").arg(vida));
    } else {
        // Crear el texto y posicionarlo en la escena, en la parte superior
        infoVida = new QGraphicsTextItem(QString("Vida: %1").arg(vida));
        infoVida->setDefaultTextColor(Qt::white);
        infoVida->setFont(QFont("Algerian", 20));
        infoVida->setPos(5, 0); // Posición en la parte superior izquierda
        if (scene()) {
            scene()->addItem(infoVida);
        }
    }
}

/*
void Heroe::disparar(int direccion)
{

}
*/
qreal obtenerPosY(const Heroe &heroe) {
    return heroe.y;
}

bool obtenerenElAire(const Heroe &heroe){
    return heroe.enElAire;
}

