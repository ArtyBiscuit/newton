#include "../newton.h"

int	destroy_vars(int keycode, t_vars *vars)
{
    (void) keycode;
    mlx_destroy_image(vars->mlx, vars->img);
	mlx_destroy_window(vars->mlx, vars->win);
    mlx_destroy_display(vars->mlx);
    free(vars->mlx);
    free(vars->win);
    free(vars->img);
    free(vars->buf);
    if (vars->planet_list)
        destroy_planet_list(vars->planet_list);
    if (vars->crt_planet)
        free(vars->crt_planet);
    free(vars->key);
    free(vars);
	return (0);
}

int render_next_frame(t_vars *vars)
{
    update_image(vars);
    if (vars->planet_list)
        update_planet_list(&(vars->planet_list), 1.5);
    print_planets(vars->planet_list);
    return (0);
}

int mouse_down(int button, int x, int y, t_vars *vars)
{
	if (button == 1)
	{
		t_planet *new_planet;
        float inv_zoom = 1.0 / vars->zoom;
		int pos_x = (x - vars->width * 0.5) * inv_zoom;
		int pos_y = (y - vars->height * 0.5) * inv_zoom;
        vars->initial_drag_x = x;
        vars->initial_drag_y = y;
		new_planet = malloc(sizeof(t_planet));
		set_planet_values(new_planet, pos_x, pos_y, 20.0, 0.0, 0.0);
		vars->crt_planet = new_planet;
        vars->key[mouse1] = 1;
	}	
	if (button == 4)
		if (vars->key[mouse1])
			set_planet_values(vars->crt_planet, vars->crt_planet->pos_x, vars->crt_planet->pos_y, vars->crt_planet->mass * 1.2, 0.0, 0.0);
	if (button == 5)
		if (vars->key[mouse1])
			set_planet_values(vars->crt_planet, vars->crt_planet->pos_x, vars->crt_planet->pos_y, vars->crt_planet->mass * 0.8, 0.0, 0.0);
	return (1);
}

int mouse_up(int button, int x, int y, t_vars *vars)
{
	if (button == 1)
	{
        vars->crt_planet->vel_x = (vars->initial_drag_x - x) * vars->zoom * 0.005;
        vars->crt_planet->vel_y = (vars->initial_drag_y - y) * vars->zoom * 0.005;
		add_planet(&(vars->planet_list), vars->crt_planet);
		vars->crt_planet = NULL;
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