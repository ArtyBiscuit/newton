#include "newton.h"

int main(void)
{
	t_vars *vars = init_vars(800, 800, "SpaceWar");
	vars->planet_list = init_planet_list(0);
	// set_planet_values(vars->planet_list[0], 0, 0, 80, 0, 0);
	// set_planet_values(vars->planet_list[1], -250, 0, 50, 0, 0.5);
	// set_planet_values(vars->planet_list[2], 250, 0, 50, 0, -0.5);
	mlx_loop(vars->mlx);
	return (0);
}
