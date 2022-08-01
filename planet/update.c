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
		if (planet_cmp(planet, planet_list[i]))
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

void check_planet_collision(t_planet ***planet_list, t_planet *planet)
{
	int i;
	float dist, dist_X, dist_Y;
	i = 0;
	while ((*planet_list)[i])
	{
		if (planet_cmp(planet, (*planet_list)[i]))
		{
			dist_X = (*planet_list)[i]->pos_x - planet->pos_x;
			dist_Y = (*planet_list)[i]->pos_y - planet->pos_y;
			dist = sqrt(dist_X * dist_X + dist_Y * dist_Y);
			if (dist <= planet->radius)
			{
				if (planet->radius > (*planet_list)[i]->radius)
				{
                    remove_planet(planet_list, (*planet_list)[i]->id);
					i--;
				}
			}
			else if (dist <= planet->radius + (*planet_list)[i]->radius)
			{
                if (planet->radius > (*planet_list)[i]->radius)
                {
					add_planet(planet_list,
					init_planet(get_max_planet_id(*planet_list),
					(*planet_list)[i]->pos_x, (*planet_list)[i]->pos_y,
					(*planet_list)[i]->mass * 0.5, (*planet_list)[i]->vel_x * 0.5, (*planet_list)[i]->vel_y * 0.5));
					set_planet_values((*planet_list)[i],
					(*planet_list)[i]->pos_x, (*planet_list)[i]->pos_y,
					(*planet_list)[i]->mass * 0.5,
					(*planet_list)[i]->vel_x * 0.5, (*planet_list)[i]->vel_y * 0.5);
                }
			}
		}
		i++;
	}
}

void update_planet_list(t_planet ***planet_list, float time)
{
    (void) time;
    t_planet **new_planet_list = copy_planet_list(*planet_list);
	int i = 0;
	while ((*planet_list)[i])
	{
		update_planet(new_planet_list, (*planet_list)[i], time);
        i++;
	}
    destroy_planet_list(new_planet_list);
    new_planet_list = copy_planet_list(*planet_list);
    i = 0;
	while ((*planet_list)[i])
	{
		if (planet_exist(new_planet_list, (*planet_list)[i]->id))
			check_planet_collision(&new_planet_list, (*planet_list)[i]);
        i++;
	}
    destroy_planet_list(*planet_list);
	*planet_list = new_planet_list;
}