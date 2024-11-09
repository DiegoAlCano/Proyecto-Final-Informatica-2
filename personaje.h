#ifndef PERSONAJE_H
#define PERSONAJE_H

class personaje
{
private:
    int x;
    int y;
    int speed_x;

public:
    personaje();
    void correr();
    void saltar();
    void morir();
    ~personaje();
};

#endif // PERSONAJE_H
