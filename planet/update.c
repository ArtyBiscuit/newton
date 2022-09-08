#include "../newton.h"

void update_planet(t_planet **planet_list, t_planet *planet, float time)
{
	int i, smooth;
	float dist, dist_X, dist_Y, norm_x, norm_y, inv_sq;
	i = 0;
	planet->acc_x = 0.0;
	planet->acc_y = 0.0;
	while (planet_list[i])
	{
		if (planet_list[i]->is_moving && planet_cmp(planet, planet_list[i]))
		{
			dist_X = planet_list[i]->pos_x - planet->pos_x;
			dist_Y = planet_list[i]->pos_y - planet->pos_y;
			smooth = 100;
			dist = sqrt(dist_X * dist_X + dist_Y * dist_Y);
			if (dist == 0)
			{
				norm_x = dist_X;
				norm_y = dist_Y;
				planet->acc_x += planet_list[i]->mass * norm_x;
				planet->acc_y += planet_list[i]->mass * norm_y;
			}
			else
			{
                inv_sq = 1.0 / (dist * dist + smooth);
				norm_x = dist_X / dist;
				norm_y = dist_Y / dist;
				planet->acc_x += planet_list[i]->mass * norm_x * inv_sq;
				planet->acc_y += planet_list[i]->mass * norm_y * inv_sq;
			}
		}
		i++;
	}
	planet->vel_x += planet->acc_x * time;
	planet->vel_y += planet->acc_y * time;
	planet->pos_x += planet->vel_x * time;
	planet->pos_y += planet->vel_y * time;
}

void update_planet_list(t_planet ***planet_list, float time)
{
    t_planet **new_planet_list = copy_planet_list(*planet_list);
	int i = 0;
	while ((*planet_list)[i])
	{
		if ((*planet_list)[i]->is_moving)
			update_planet(new_planet_list, (*planet_list)[i], time);
        i++;
	}
    destroy_planet_list(new_planet_list);
}