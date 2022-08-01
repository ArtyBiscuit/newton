#include "../newton.h"

void draw_planet(t_vars *vars, t_planet *planet)
{
	int x, y, radius;
	radius = vars->zoom * planet->radius;
	x = (vars->off_x + planet->pos_x) * vars->zoom;
	y = (vars->off_y + planet->pos_y) * vars->zoom;
	for(int i = y - radius; i < y + radius; i++)
	{
		for(int j = x - radius; j < x + radius; j++)
		{
			if ((i - y) * (i - y) + (j - x) * (j - x) <= radius * radius)
			{
				if (i >= 0 && j >= 0 && i < vars->height && j < vars->width)
				{
					int pixel = (i * vars->line_length) + (j * 4);
					if (vars->endian == 1)        // Most significant (Alpha) byte first
					{
						vars->buf[pixel + 0] = (planet->color >> 24);
						vars->buf[pixel + 1] = (planet->color >> 16) & 0xFF;
						vars->buf[pixel + 2] = (planet->color >> 8) & 0xFF;
						vars->buf[pixel + 3] = (planet->color) & 0xFF;
					}
					else if (vars->endian == 0)   // Least significant (Blue) byte first
					{
						vars->buf[pixel + 0] = (planet->color) & 0xFF;
						vars->buf[pixel + 1] = (planet->color >> 8) & 0xFF;
						vars->buf[pixel + 2] = (planet->color >> 16) & 0xFF;
						vars->buf[pixel + 3] = (planet->color >> 24);
					}
				}
			}
		}
	}
}

void draw_planet_list(t_vars *vars, t_planet **planet_list)
{
    int i = 0;
    while (planet_list[i])
        draw_planet(vars, planet_list[i++]);
}

void update_image(t_vars *vars)
{
    reset_image(vars->buf, 4 * vars->width * vars->height);
    if (vars->crt_planet)
        draw_planet(vars, vars->crt_planet);
    if (vars->planet_list)
        draw_planet_list(vars, vars->planet_list);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
}