#include "../newton.h"

int key_press(int keycode, t_vars *data)
{
	// printf("Keycode : %d\n", keycode);
	if (keycode == 45)
		data->key[minus] = 1;
	else if (keycode == 61)
		data->key[plus] = 1;
	else if (keycode == 100)
		data->key[d] = 1;
	else if (keycode == 97)
		data->key[a] = 1;
	else if (keycode == 65364)
		data->key[up] = 1;
	else if (keycode == 65363)
		data->key[left] = 1;
	else if (keycode == 65362)
		data->key[bottom] = 1;
	else if (keycode == 65361)
		data->key[right] = 1;
	else if (keycode == 32)
		data->key[space] = 1;
	else if (keycode == 119)
		data->key[w] = 1;
	return 1;
}

int key_release(int keycode, t_vars *data)
{
	if (keycode == 45)
		data->key[minus] = 0;
	else if (keycode == 61)
		data->key[plus] = 0;
	else if (keycode == 100)
		data->key[d] = 0;
	else if (keycode == 97)
		data->key[a] = 0;
	else if (keycode == 65364)
		data->key[up] = 0;
	else if (keycode == 65363)
		data->key[left] = 0;
	else if (keycode == 65362)
		data->key[bottom] = 0;
	else if (keycode == 65361)
		data->key[right] = 0;
	else if (keycode == 32)
		data->key[space] = 0;
	if (keycode == 119)
		data->key[w] = 0;
	return 1;
}

void update_controls(t_vars *data)
{
	int offset = 20;

	if (data->key[minus])
		data->zoom *= 0.9;
	if (data->key[plus])
		data->zoom *= 1.1;
	if (data->key[d])
		data->ship->angle += 0.1;
	if (data->key[a])
		data->ship->angle -= 0.1;
	if (data->key[up])
		data->offset_Y -= offset / data->zoom;
	if (data->key[left])
		data->offset_X -= offset / data->zoom;
	if (data->key[bottom])
		data->offset_Y += offset / data->zoom;
	if (data->key[right])
		data->offset_X += offset / data->zoom;
	if (data->key[space])
		data->is_playing = !data->is_playing;
}

int mouse_down(int button, int x, int y, t_vars *data)
{
	if (button == 1)
	{
		t_planet *new_planet;
		int x_rel = ((x - data->width / 2) / data->zoom) - data->offset_X;
		int y_rel = ((y - data->height / 2) / data->zoom) - data->offset_Y;
		new_planet = malloc(sizeof(t_planet));
		set_planet_values(new_planet, x_rel, y_rel, 20.0, 0.0, 0.0);
		data->edit_planet = new_planet;
		data->lauch_coX = x;
		data->lauch_coY = y;
		data->key[mouse1] = 1;
	}
	if (button == 4)
		if (data->key[mouse1])
			set_planet_values(data->edit_planet, data->edit_planet->x, data->edit_planet->y, data->edit_planet->mass * 1.2, 0.0, 0.0);
	if (button == 5)
		if (data->key[mouse1])
			set_planet_values(data->edit_planet, data->edit_planet->x, data->edit_planet->y, data->edit_planet->mass * 0.8, 0.0, 0.0);
	
	return (1);
}

int mouse_up(int button, int x, int y, t_vars *data)
{
	if (button == 1)
	{
		data->edit_planet->speed_X = data->lauch_coX - x;
		data->edit_planet->speed_Y = data->lauch_coY - y;
		add_planet(data->edit_planet, &data->planets);
		data->edit_planet = NULL;
		data->key[mouse1] = 0;
	}
	return (1);
}