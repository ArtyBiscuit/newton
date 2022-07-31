#include "../newton.h"

t_ship *init_ship(int id, double x, double y, int size)
{
	t_ship *ship = malloc(sizeof(t_ship));
	ship->id = id;
	ship->x = x;
	ship->y = y;
	ship->speed_X = 0.0;
	ship->speed_Y = 0.0;
	ship->angle = 0.0;;
	ship->acceleration_Y = 0.0;
	ship->acceleration_X = 0.0;
	ship->size = size;
	ship->littledot = init_littledot(ship, 5);
	return (ship);
}

void update_ship(t_vars *data, t_planet **planets, t_ship *ship, float time)
{
	int i, smooth;
	float dist, dist_X, dist_Y, norm_x, norm_y;
	
	i = 0;
	ship->acceleration_X = 0.0;
	ship->acceleration_Y = 0.0;
	while (planets[i])
	{
		dist_X = planets[i]->x - ship->x;
		dist_Y = planets[i]->y - ship->y;
		smooth = 100;

		dist = sqrt(dist_X * dist_X + dist_Y * dist_Y);
		if (dist == 0)
		{
			norm_x = dist_X;
			norm_y = dist_Y;
			ship->acceleration_X += planets[i]->mass * norm_x;
			ship->acceleration_Y += planets[i]->mass * norm_y;
		}
		else
		{
			norm_x = dist_X / dist;
			norm_y = dist_Y / dist;
			ship->acceleration_X += planets[i]->mass * norm_x / (dist * dist + smooth);
			ship->acceleration_Y += planets[i]->mass * norm_y / (dist * dist + smooth);
		}
		i++;
	}
	if (data->key[w])
	{
		ship->acceleration_X += cos(ship->angle) * 0.01;
		ship->acceleration_Y += sin(ship->angle) * 0.01;
	}
	ship->speed_X += ship->acceleration_X * time;
	ship->speed_Y += ship->acceleration_Y * time;
	ship->x += ship->speed_X * time;
	ship->y += ship->speed_Y * time;
	update_littledot(ship);
}

void destroy_ship(t_ship *ship)
{
	free(ship->littledot);
	free(ship);
}