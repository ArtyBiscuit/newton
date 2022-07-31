#include "../newton.h"

t_vars *init_vars(int width, int height, char *title, t_planet **planets, t_ship *ship)
{
	t_vars *data;

	data = malloc(sizeof(t_vars));
	data->key = malloc(sizeof(int) * 11);
	for (int i = 0; i < 11; i++)
		data->key[i] = 0;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, width, height, title);
	data->width = width;
	data->height = height;
	data->img = NULL;
	data->buff = NULL;
	data->endian = 0;
	data->line_length = 0;
	data->bits_per_pixel = 0;
	data->offset_X = 0;
	data->offset_Y = 0;
	data->zoom = 1.0;
	data->planets = planets;
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	data->buff = mlx_get_data_addr(data->img, &(data->bits_per_pixel), &(data->line_length), &(data->endian));
	data->is_playing = 0;
	data->ship = ship;
	data->lauch_coX = 0;
	data->lauch_coY = 0;
	data->edit_planet = NULL;
	mlx_loop_hook(data->mlx, render_next_frame, data);
	mlx_hook(data->win, 2, (1L<<0), key_press, data);
	mlx_hook(data->win, 3, (1L<<1), key_release, data);
	mlx_hook(data->win, 4, (1L<<2), mouse_down, data);
	mlx_hook(data->win, 5, (1L<<3), mouse_up, data);
	return (data);
}


void draw_ship(t_vars *data, t_ship *ship)
{
	int size = data->zoom * ship->size;
	int x = (data->offset_X + ship->x) * data->zoom;
	int y = (data->offset_Y + ship->y) * data->zoom;
	x += data->width / 2;
	y += data->height / 2;
	for (int i = y - (size / 2); i < y + (size / 2); i++)
	{
		for (int j = x - (size / 2); j < x + (size / 2); j++)
		{
			if (i >= 0 && j >= 0 && i < data->height && j < data->width)
			{
				int pixel = (i * data->line_length) + (j * 4);

				if (data->endian == 1)        // Most significant (Alpha) byte first
				{
					data->buff[pixel + 0] = (0xFFFFFFFF >> 24);
					data->buff[pixel + 1] = (0xFFFFFFFF >> 16) & 0xFF;
					data->buff[pixel + 2] = (0xFFFFFFFF >> 8) & 0xFF;
					data->buff[pixel + 3] = (0xFFFFFFFF) & 0xFF;
				}
				else if (data->endian == 0)   // Least significant (Blue) byte first
				{
					data->buff[pixel + 0] = (0xFFFFFFFF) & 0xFF;
					data->buff[pixel + 1] = (0xFFFFFFFF >> 8) & 0xFF;
					data->buff[pixel + 2] = (0xFFFFFFFF >> 16) & 0xFF;
					data->buff[pixel + 3] = (0xFFFFFFFF >> 24);
				}
			}
		}
	}
	draw_littledot(data, ship->littledot);
}

void draw_littledot(t_vars *data, t_littledot *littledot)
{
	int size = data->zoom * littledot->size;
	int x = (data->offset_X + littledot->x) * data->zoom;
	int y = (data->offset_Y + littledot->y) * data->zoom;
	x += data->width / 2;
	y += data->height / 2;
	for (int i = y - (size / 2); i < y + (size / 2); i++)
	{
		for (int j = x - (size / 2); j < x + (size / 2); j++)
		{
			if (i >= 0 && j >= 0 && i < data->height && j < data->width)
			{
				int pixel = (i * data->line_length) + (j * 4);

				if (data->endian == 1)        // Most significant (Alpha) byte first
				{
					data->buff[pixel + 0] = (littledot->color >> 24);
					data->buff[pixel + 1] = (littledot->color >> 16) & 0xFF;
					data->buff[pixel + 2] = (littledot->color >> 8) & 0xFF;
					data->buff[pixel + 3] = (littledot->color) & 0xFF;
				}
				else if (data->endian == 0)   // Least significant (Blue) byte first
				{
					data->buff[pixel + 0] = (littledot->color) & 0xFF;
					data->buff[pixel + 1] = (littledot->color >> 8) & 0xFF;
					data->buff[pixel + 2] = (littledot->color >> 16) & 0xFF;
					data->buff[pixel + 3] = (littledot->color >> 24);
				}
			}
		}
	}
}

void draw_planet(t_vars *data, t_planet *planet)
{
	int x;
	int y;
	int	radius;

	radius = data->zoom * planet->radius;
	x = (data->offset_X + planet->x) * data->zoom;
	y = (data->offset_Y + planet->y) * data->zoom;
	x += data->width / 2;
	y += data->height / 2;
	for(int i = y - radius; i < y + radius; i++)
	{
		for(int j = x - radius; j < x + radius; j++)
		{
			if ((i - y) * (i - y) + (j - x) * (j - x) <= radius * radius)
			{
				if (i >= 0 && j >= 0 && i < data->height && j < data->width)
				{
					int pixel = (i * data->line_length) + (j * 4);

					if (data->endian == 1)        // Most significant (Alpha) byte first
					{
						data->buff[pixel + 0] = (planet->color >> 24);
						data->buff[pixel + 1] = (planet->color >> 16) & 0xFF;
						data->buff[pixel + 2] = (planet->color >> 8) & 0xFF;
						data->buff[pixel + 3] = (planet->color) & 0xFF;
					}
					else if (data->endian == 0)   // Least significant (Blue) byte first
					{
						data->buff[pixel + 0] = (planet->color) & 0xFF;
						data->buff[pixel + 1] = (planet->color >> 8) & 0xFF;
						data->buff[pixel + 2] = (planet->color >> 16) & 0xFF;
						data->buff[pixel + 3] = (planet->color >> 24);
					}
				}
			}
		}
	}
	/*
	int i = 0;
	while (i < data->width)
	{
		for (int j = 0; j < data->height; j++)
		{
			data->buff[j * data->line_length + i * 4 + 1] = 255;
		}
		i += data->width / 10 * data->zoom;
	}
	*/
}

void update_image(t_vars *data, t_planet **planets, t_ship *ship)
{

	int i;

	i = 4 * data->width * data->height;
	while (i--)
		data->buff[i] = 0;
	i = 0;
	while (planets[i])
	{
		draw_planet(data, planets[i]);
		i++;
	}
	draw_ship(data, ship);
	if (data->edit_planet)
	{
		draw_planet(data, data->edit_planet);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

int render_next_frame(t_vars *data)
{
	// print_planets(data->planets);
	update_controls(data);
	update_image(data, data->planets, data->ship);
	if (data->is_playing)
	{
		update_planets(&(data->planets), 1.5);
		update_ship(data, data->planets, data->ship, 1.5);
	}
	return 1;
}