#include "../newton.h"

void reset_image(char *buf, int len)
{
    while (len--)
        buf[len] = 0;
}

void check_planet_buf(t_vars *vars)
{
	if (vars->crt_planet && vars->crt_planet->is_moving)
	{
		add_planet(&(vars->planet_list), vars->crt_planet);
		vars->crt_planet = NULL;
	}
}