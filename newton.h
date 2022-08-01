#ifndef NEWTON_H
# define NEWTON_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "mlx/mlx.h"

#define NB_KEYS 1

typedef enum s_key {
	mouse1
} t_key;

typedef struct s_planet
{
	int 	id;
	double pos_x, pos_y;
	double mass, radius;
	double vel_x, vel_y;
	double acc_x, acc_y;
	int color;
} t_planet;

typedef struct s_vars
{
	void *mlx;
	void *win;
	int width;
	int height;
	void *img;
	char *buf;
	int endian;
	int bits_per_pixel;
	int line_length;
	int off_x;
	int off_y;
	double zoom;
	t_planet **planet_list;
	t_planet *crt_planet;
	int initial_drag_x;
	int initial_drag_y;
	int *key;
} t_vars;

/*===========================*/
/*			PLANET			 */
/*===========================*/

// planet/init.c
t_planet *init_planet(int id, int pos_x, int pos_y, double mass, double vel_x, double vel_y);
t_planet **init_planet_list(int nb_planets);
void destroy_planet_list(t_planet **planet_list);
// planet/utils.c
int calcul_planet_color(double mass);
int calcul_planet_radius(double mass);
void set_planet_values(t_planet *planet, int pos_x, int pos_y, double mass, double vel_x, double vel_y);
int get_nb_planet(t_planet **planet_list);
t_planet *copy_planet(t_planet *planet);
t_planet **copy_planet_list(t_planet **planet_list);
int planet_cmp(t_planet *planet_A, t_planet *planet_B);
void print_planets(t_planet **planets);
void add_planet(t_planet ***planet_list, t_planet *planet);
void remove_planet(t_planet ***planet_list, int id);
int planet_exist(t_planet **planet_list, int id);
int get_max_planet_id(t_planet **planet_list);
t_planet *get_planet_from_id(t_planet **planet_list, int id);
// planet/update.c
void update_planet(t_planet **planet_list, t_planet *planet, float time);
void update_planet_list(t_planet ***planet_list, float time);

/*===========================*/
/*			VARS			 */
/*===========================*/

// vars/init.c
t_vars *init_vars(int width, int height, char *title);
int *init_keys(void);
void init_mlx_hook(t_vars *vars);
// vars/hook.c
int	destroy_vars(int keycode, t_vars *vars);
int render_next_frame(t_vars *vars);
int mouse_down(int button, int x, int y, t_vars *vars);
int mouse_up(int button, int x, int y, t_vars *vars);
// vars/draw.c
void draw_planet(t_vars *vars, t_planet *planet);
void draw_planet_list(t_vars *vars, t_planet **planet_list);
void update_image(t_vars *vars);
// vars/utils.c
void reset_image(char *buf, int len);

#endif