#include "../newton.h"

t_planet *init_planet(int id, int pos_x, int pos_y, double mass, double vel_x, double vel_y)
{
    t_planet *planet = malloc(sizeof(t_planet));
    planet->id = id;
    planet->pos_x = pos_x;
    planet->pos_y = pos_y;
    planet->mass = mass;
    planet->vel_x = vel_x;
    planet->vel_y = vel_y;
    planet->acc_x = 0.0;
    planet->acc_y = 0.0;
    planet->color = calcul_planet_color(planet->mass);
	planet->radius = calcul_planet_radius(planet->mass);
    planet->is_moving = 1;
    return (planet);
}

t_planet **init_planet_list(int nb_planets)
{
    t_planet **planet_list = malloc(sizeof(t_planet *) * (nb_planets + 1));
    planet_list[nb_planets] = NULL;
    for (int i = 0; i < nb_planets; i++)
        planet_list[i] = init_planet(i, 0, 0, 0, 0, 0);
    return (planet_list);
}

void destroy_planet_list(t_planet **planet_list)
{
    int i = 0;
    while (planet_list[i])
        free(planet_list[i++]);
    free(planet_list);
}

