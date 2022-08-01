#include "../newton.h"

int calcul_planet_color(double mass)
{
	if (mass <= 250)
		return (0xFF00FF00 + (((int) (255.0 * (1 - mass / 250.0))) << 16) + ((int) (255.0 * (1 - mass / 250.0))));
	else if (mass <= 500)
		return (0xFF00FF00 + (((int) (255.0 * (1 - (mass - 250.0) / 250.0))) << 16));
	else if (mass <= 1000)
		return (0xFFFF0000 + (((int) (255.0 * (1 - (mass - 500.0) / 500.0))) << 8));
	else
		return (0xFFFF0000);
}

int calcul_planet_radius(double mass)
{
	return (cbrt(300.0 * mass / (4.0 * 3.14)));
}

void set_planet_values(t_planet *planet, int pos_x, int pos_y, double mass, double vel_x, double vel_y)
{
    planet->pos_x = pos_x;
    planet->pos_y = pos_y;
    planet->mass = mass;
    planet->vel_x = vel_x;
    planet->vel_y = vel_y;
    planet->color = calcul_planet_color(planet->mass);
	planet->radius = calcul_planet_radius(planet->mass);
}

int get_nb_planet(t_planet **planet_list)
{
	int len = 0;
	while (planet_list[len])
		len++;
	return (len);
}

t_planet *copy_planet(t_planet *planet)
{
	t_planet *new_planet = malloc(sizeof(t_planet));
	new_planet->id = planet->id;
	new_planet->pos_x = planet->pos_x;
	new_planet->pos_y = planet->pos_y;
	new_planet->mass = planet->mass;
	new_planet->radius = planet->radius;
	new_planet->color = planet->color;
	new_planet->vel_x = planet->vel_x;
	new_planet->vel_y = planet->vel_y;
	new_planet->acc_x = planet->acc_x;
	new_planet->acc_y = planet->acc_y;
	return (new_planet);
}

t_planet **copy_planet_list(t_planet **planet_list)
{
	t_planet **new_planet_list;
	int nb_planets = get_nb_planet(planet_list);
	new_planet_list = malloc(sizeof(t_planet *) * (nb_planets + 1));
	new_planet_list[nb_planets] = NULL;
	while (nb_planets--)
		new_planet_list[nb_planets] = copy_planet(planet_list[nb_planets]);
	return (new_planet_list);
}

int planet_cmp(t_planet *planet_A, t_planet *planet_B)
{
	if (!planet_A || !planet_B)
		return (1);
	return (planet_A->id != planet_B->id);
}

void add_planet(t_planet ***planet_list, t_planet *planet)
{
	t_planet **new_planet_list;
	int nb_planets = get_nb_planet(*planet_list);
	new_planet_list = malloc(sizeof(t_planet *) * (nb_planets + 2));
	new_planet_list[nb_planets + 1] = NULL;
	new_planet_list[nb_planets] = planet;
	while (nb_planets--)
		new_planet_list[nb_planets] = copy_planet((*planet_list)[nb_planets]);
	destroy_planet_list(*planet_list);
	*planet_list = new_planet_list;
}

void remove_planet(t_planet ***planet_list, int id)
{
	t_planet **new_planet_list;
	int nb_planets = get_nb_planet(*planet_list);
	new_planet_list = malloc(sizeof(t_planet *) * (nb_planets));
	new_planet_list[nb_planets--] = NULL;
	while (nb_planets--)
		if ((*planet_list)[nb_planets]->id != id)
			new_planet_list[nb_planets] = copy_planet((*planet_list)[nb_planets]);
	destroy_planet_list(*planet_list);
	*planet_list = new_planet_list;
}

void print_planets(t_planet **planets)
{
	int i;

	system("clear");
	i = 0;
	while (planets[i])
	{
		printf("Planet-%d:\n", i);
		printf("\tMasse: %f\n", planets[i]->mass);
		printf("\tCoords:\n");
		printf("\t\tX: %f\n", planets[i]->pos_x);
		printf("\t\tY: %f\n", planets[i]->pos_y);
		printf("\tSpeed:\n");
		printf("\t\tX: %f\n", planets[i]->vel_x);
		printf("\t\tY: %f\n", planets[i]->vel_y);
		printf("\tAcceleration:\n");
		printf("\t\tX: %f\n", planets[i]->acc_x);
		printf("\t\tY: %f\n", planets[i]->acc_y);
		i++;
	}
	printf("\n");
}

int planet_exist(t_planet **planet_list, int id)
{
	int i = 0;
	while (planet_list[i])
	{
		if (planet_list[i]->id == id)
			return (1);
		i++;
	}
	return (0);
}

int get_max_planet_id(t_planet **planet_list)
{
	int max_id = 0;
	int i = 1;
	while (planet_list[i])
	{
		if (planet_list[i] > planet_list[max_id])
			max_id = i;
		i++;
	}
	return (planet_list[max_id]->id);
}

t_planet *get_planet_from_id(t_planet **planet_list, int id)
{
	int i = 0;
	while (planet_list[i])
	{
		if (planet_list[i]->id == id)
			return (planet_list[i]);
		i++;
	}
	return (NULL);
}