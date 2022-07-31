#include "../newton.h"

int planet_cmp(const t_planet *a, const t_planet *b)
{
	return (a->id == b->id);
}

t_planet **init_planets(int nb_planets)
{
	t_planet **planets;
	int id;

	planets = malloc(sizeof(t_planet) * (nb_planets + 1));
	planets[nb_planets] = NULL;
	id = 0;
	while (nb_planets--)
	{
		planets[nb_planets] = malloc(sizeof(t_planet));
		planets[nb_planets]->speed_X = 0.0;
		planets[nb_planets]->speed_Y = 0.0;
		planets[nb_planets]->acceleration_X = 0.0;
		planets[nb_planets]->acceleration_Y = 0.0;
		planets[nb_planets]->x = 0.0;
		planets[nb_planets]->y = 0.0;
		planets[nb_planets]->radius = 0.0;
		planets[nb_planets]->mass = 0.0;
		planets[nb_planets]->id = id++;
		planets[nb_planets]->color = 0;
	}
	return (planets);
}

void set_planet_values(t_planet *planet, double x, double y, double mass, double speed_X, double speed_Y)
{
	planet->speed_X = speed_X;
	planet->speed_Y = speed_Y;
	planet->x = x;
	planet->y = y;
	planet->mass = mass;
	if (mass <= 250)
	{
		planet->color = 0xFF000000;
		planet->color += ((int) (255.0 * (1 - mass / 250.0))) << 16;
		planet->color += 255 << 8;
		planet->color += ((int) (255.0 * (1 - mass / 250.0)));
	}
	else if (mass <= 500)
	{
		planet->color = 0xFF000000;
		planet->color += ((int) (255.0 * (1 - (mass - 250.0) / 250.0))) << 16;
		planet->color += 255 << 8;
	} 
	else if (mass <= 1000)
	{
		planet->color = 0xFF000000;
		planet->color += 255 << 16;
		planet->color += ((int) (255.0 * (1 - (mass - 500.0) / 500.0))) << 8;
	}
	else
		planet->color = 0xFFFF0000;
	planet->radius = cbrt(300.0 * mass / (4.0 * 3.14));
}

void destroy_planets(t_planet **planets)
{
	int i = 0;
	while (planets[i])
		free(planets[i++]);
	free(planets);
}

void update_planet(t_planet **planets, t_planet *planet, float time)
{
	int i, smooth;
	float dist, dist_X, dist_Y, norm_x, norm_y;
	
	i = 0;
	planet->acceleration_X = 0.0;
	planet->acceleration_Y = 0.0;
	while (planets[i])
	{
		if (!planet_cmp(planet, planets[i]))
		{
			dist_X = planets[i]->x - planet->x;
			dist_Y = planets[i]->y - planet->y;
			smooth = 100;

			dist = sqrt(dist_X * dist_X + dist_Y * dist_Y);
			if (dist == 0)
			{
				norm_x = dist_X;
				norm_y = dist_Y;
				planet->acceleration_X += planets[i]->mass * norm_x;
				planet->acceleration_Y += planets[i]->mass * norm_y;
			}
			else
			{
				norm_x = dist_X / dist;
				norm_y = dist_Y / dist;
				planet->acceleration_X += planets[i]->mass * norm_x / (dist * dist + smooth);
				planet->acceleration_Y += planets[i]->mass * norm_y / (dist * dist + smooth);
			}
		}
		i++;
	}
	planet->speed_X += planet->acceleration_X * time;
	planet->speed_Y += planet->acceleration_Y * time;
	planet->x += planet->speed_X * time;
	planet->y += planet->speed_Y * time;
}

int get_nb_planets(t_planet **planet)
{
	int len;

	len = 0;
	while (planet[len])
		len++;
	return (len);
}

t_planet **copy_planet_list(t_planet **planets)
{
	t_planet **new_planets;
	int i, nb_planets;

	nb_planets = get_nb_planets(planets);
	new_planets = init_planets(nb_planets);
	i = 0;
	while (planets[i])
	{
		new_planets[i]->speed_X = planets[i]->speed_X;
		new_planets[i]->speed_Y = planets[i]->speed_Y;
		new_planets[i]->acceleration_X = planets[i]->acceleration_X;
		new_planets[i]->acceleration_Y = planets[i]->acceleration_Y;
		new_planets[i]->x = planets[i]->x;
		new_planets[i]->y = planets[i]->y;
		new_planets[i]->mass = planets[i]->mass;
		new_planets[i]->radius = planets[i]->radius;
		new_planets[i]->color = planets[i]->color;
		new_planets[i]->id = planets[i]->id;
		i++;
	}
	return (new_planets);
}

void update_planets(t_planet ***planets, float time)
{
	t_planet **planet_tmp;
	int i;

	planet_tmp = copy_planet_list(*planets);
	i = 0;
	while ((*planets)[i])
		update_planet(*planets, planet_tmp[i++], time);
	destroy_planets(*planets);
	*planets = planet_tmp;
}

void add_planet(t_planet *planet, t_planet ***planets)
{
	t_planet **new_planets;
	int i, nb_planets;

	nb_planets = get_nb_planets(*planets);
	new_planets = init_planets(nb_planets + 1);
	i = 0;
	while ((*planets)[i])
	{
		new_planets[i]->speed_X = (*planets)[i]->speed_X;
		new_planets[i]->speed_Y = (*planets)[i]->speed_Y;
		new_planets[i]->acceleration_X = (*planets)[i]->acceleration_X;
		new_planets[i]->acceleration_Y = (*planets)[i]->acceleration_Y;
		new_planets[i]->x = (*planets)[i]->x;
		new_planets[i]->y = (*planets)[i]->y;
		new_planets[i]->mass = (*planets)[i]->mass;
		new_planets[i]->radius = (*planets)[i]->radius;
		new_planets[i]->color = (*planets)[i]->color;
		new_planets[i]->id = (*planets)[i]->id;
		i++;
	}
	set_planet_values(new_planets[i], planet->x, planet->y, planet->mass, planet->speed_X, planet->speed_Y);
	destroy_planets(*planets);
	free(planet);
	*planets = new_planets;
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
		printf("\t\tX: %f\n", planets[i]->x);
		printf("\t\tY: %f\n", planets[i]->y);
		printf("\tSpeed:\n");
		printf("\t\tX: %f\n", planets[i]->speed_X);
		printf("\t\tY: %f\n", planets[i]->speed_Y);
		printf("\tAcceleration:\n");
		printf("\t\tX: %f\n", planets[i]->acceleration_X);
		printf("\t\tY: %f\n", planets[i]->acceleration_Y);
		i++;
	}
	printf("\n");
}