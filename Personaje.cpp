#include "Personaje.h"

Personaje::Personaje(unsigned short _SpriteX, unsigned short _SpriteY, unsigned short _spriteAncho, unsigned short _spriteAlto)
{
    SpriteX = _SpriteX;
    SpriteY = _SpriteY;
    spriteAncho = _spriteAncho;
    spriteAlto = _spriteAlto;
}


void Personaje::secuenciaSprite(short direccion, unsigned short maxContador)
{
    SpriteY = direccion;
    SpriteX = spriteAncho*contador;
    sprite = hojaSprites.copy(SpriteX,SpriteY,spriteAncho,spriteAlto);
    setPixmap(sprite);
    contador++;
    if(contador==maxContador){
        contador = 0;
    }
}
