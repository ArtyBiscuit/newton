#include "../newton.h"

t_littledot *init_littledot(t_ship *ship, int size)
{
    t_littledot *littledot;

    littledot = malloc(sizeof(t_littledot));
    littledot->color = 0xFFFF0000;
    littledot->size = size;
    littledot->x = ship->x + cos(ship->angle) * ship->size;
    littledot->y = ship->y + sin(ship->angle) * ship->size;
    return (littledot);
}

void update_littledot(t_ship *ship)
{
    ship->littledot->x = ship->x + cos(ship->angle) * ship->size;
    ship->littledot->y = ship->y + sin(ship->angle) * ship->size;
}