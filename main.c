#include "newton.h"

int main(void)
{
	t_planet **planets;
	t_vars *data;
	t_ship *ship;

	planets = init_planets(3);
	set_planet_values(planets[0], -350, 0, 50, 0, 0.5);
	set_planet_values(planets[1], 0, 0, 150, 0, 0);
	set_planet_values(planets[2], 350, 0, 50, 0, -0.5);

	

	ship = init_ship(0, -250.0, -250.0, 10);
	data = init_vars(3840, 2160, "Spacewar", planets, ship);
	update_image(data, data->planets, ship);


	/*
	data->img = mlx_new_image(data->mlx, width, height);
	data->buff = mlx_get_vars_addr(data->img, &(data->bits_per_pixel), &(data->line_length), &(data->endian));
	*/
	mlx_loop(data->mlx);
	destroy_planets(planets);
	destroy_ship(ship);
	free(data->key);
	return (0);
}
