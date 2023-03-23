#include "../include/cub3d.h"

t_m	*setup_main(void)
{
	t_m	*m;

	m = malloc(sizeof(t_m));
	m->mlx = NULL;
	m->img = NULL;
	m->window_h = 1080;
	m->window_w = 1920;
	m->input = NULL;
	m->h = 0;
	m->w = 0;
	m->fd = 0;
	return (m);
}
