#include "../../include/cub3d.h"

void	game_loop(t_m *m)
{
	int			x;
	// int			y;
	t_camera	camera;

	x = -1;
	while (++x < m->w)
	{
		camera = (t_camera) {2 * x / (double) m->w - 1, 0, m->player->dir_x + m->player->plane_x * camera.x, m->player->dir_y + m->player->pos_y * camera.y};
	}
}

