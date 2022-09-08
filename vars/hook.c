#include "../newton.h"

int	destroy_vars(int keycode, t_vars *vars)
{
    (void) keycode;
    (void) vars;
	mlx_loop_end(vars->mlx);
	return (0);
}

int render_next_frame(t_vars *vars)
{
	check_planet_buf(vars);
    update_image(vars);
    if (vars->planet_list)
        update_planet_list(&(vars->planet_list), 1.5);
    print_planets(vars->planet_list);
    return (0);
}

t_planet *get_planet_with_pos(int x, int y, t_vars *vars)
{
	int i = 0;
	while (vars->planet_list[i])
	{
		int dist_x = x - (vars->planet_list[i]->pos_x + vars->off_x) * vars->zoom;
		int dist_y = y - (vars->planet_list[i]->pos_y + vars->off_y) * vars->zoom;
		int dist = sqrt(dist_x * dist_x + dist_y * dist_y);
		if (dist < vars->planet_list[i]->radius)
			return (vars->planet_list[i]);
		i++;
	}
	return (NULL);
}

int mouse_down(int button, int x, int y, t_vars *vars)
{
	t_planet *planet;

	if (button == 1)
	{
		if ((planet = get_planet_with_pos(x, y, vars)))
		{
			planet->is_moving = 0;
			vars->initial_drag_x = x;
			vars->initial_drag_y = y;
			vars->crt_planet = planet;
			vars->key[mouse1] = 1;
		}
		else
		{
			t_planet *new_planet;
			float inv_zoom = 1.0 / vars->zoom;
			int pos_x = (x - vars->width * 0.5) * inv_zoom;
			int pos_y = (y - vars->height * 0.5) * inv_zoom;
			vars->initial_drag_x = x;
			vars->initial_drag_y = y;
			new_planet = malloc(sizeof(t_planet));
			set_planet_values(new_planet, pos_x, pos_y, 20.0, 0.0, 0.0);
			new_planet->is_moving = 0;
			vars->crt_planet = new_planet;
			vars->key[mouse1] = 1;
		}
	}	
	if (button == 4)
		if (vars->key[mouse1])
			set_planet_values(vars->crt_planet, vars->crt_planet->pos_x, vars->crt_planet->pos_y, vars->crt_planet->mass * 1.2, 0.0, 0.0);
	if (button == 5)
		if (vars->key[mouse1])
			set_planet_values(vars->crt_planet, vars->crt_planet->pos_x, vars->crt_planet->pos_y, vars->crt_planet->mass * 0.8, 0.0, 0.0);
	return (1);
}

t_planet *get_planet_not_moving(t_planet **planet_list)
{
	int i = 0;
	while (planet_list[i])
	{
		if (!planet_list[i]->is_moving)
			return (planet_list[i]);
		i++;
	}
	return (NULL);
}

int mouse_up(int button, int x, int y, t_vars *vars)
{
	if (button == 1)
	{
		vars->crt_planet->vel_x = (vars->initial_drag_x - x) * vars->zoom * 0.005;
		vars->crt_planet->vel_y = (vars->initial_drag_y - y) * vars->zoom * 0.005;
		vars->crt_planet->is_moving = 1;
		vars->key[mouse1] = 0;
	}
	if (button == 4)
		if (vars->key[mouse1])
			set_planet_values(vars->crt_planet, vars->crt_planet->pos_x, vars->crt_planet->pos_y, vars->crt_planet->mass * 1.2, 0.0, 0.0);
	if (button == 5)
		if (vars->key[mouse1])
			set_planet_values(vars->crt_planet, vars->crt_planet->pos_x, vars->crt_planet->pos_y, vars->crt_planet->mass * 0.8, 0.0, 0.0);
	return (1);
}