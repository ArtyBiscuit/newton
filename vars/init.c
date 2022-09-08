#include "../newton.h"

t_vars *init_vars(int width, int height, char *title)
{
    (void) title;
    t_vars *vars = malloc(sizeof(t_vars));
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, width, height, title);
	vars->width = width;
	vars->height = height;
	vars->img = mlx_new_image(vars->mlx, width, height);
	vars->buf = mlx_get_data_addr(vars->img, &(vars->bits_per_pixel), &(vars->line_length), &(vars->endian));
    vars->off_x = width * 0.5;
    vars->off_y = height * 0.5;
    vars->zoom = 1.0;
    vars->planet_list = NULL;
    vars->crt_planet = NULL;
    vars->initial_drag_x = 0;
    vars->initial_drag_y = 0;
    vars->key = init_keys();
    init_mlx_hook(vars);
    return (vars);
}

int *init_keys(void)
{
    int *key;

    key = malloc(sizeof(int) * NB_KEYS);
    for (int i = 0; i < NB_KEYS; i++)
        key[i] = 0;
    return (key);
}

void init_mlx_hook(t_vars *vars)
{
	mlx_loop_hook(vars->mlx, render_next_frame, vars);
    mlx_hook(vars->win, 17, 0L, destroy_vars, vars);
	mlx_hook(vars->win, 4, (1L<<2), mouse_down, vars);
	mlx_hook(vars->win, 5, (1L<<3), mouse_up, vars);
}