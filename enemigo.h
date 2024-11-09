#ifndef ENEMIGO_H
#define ENEMIGO_H
#include "personaje.h"

class enemigo: public personaje
{
private:
    int spriteAncho;
    int spriteLargo;

public:
    enemigo();
    void ataqueCuerpo();
};

#endif // ENEMIGO_H
