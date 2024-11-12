#include "Personaje.h"

Personaje::Personaje(int _SpriteX, int _SpriteY, int _spriteAncho,int _spriteAlto)
{
    SpriteX = _SpriteX;
    SpriteY = _SpriteY;
    spriteAncho = _spriteAncho;
    spriteAlto = _spriteAlto;
}


void Personaje::secuenciaSprite(int direccion, int maxContador)
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
