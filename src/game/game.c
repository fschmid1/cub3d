/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 17:33:26 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/24 19:30:37 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	game_loop(t_m *main)
{
	int			x;
	t_camera	camera;
	t_map		*m;

	m = main->map;
	x = -1;
	while (++x < main->window_w)
	{
		double	cameraX = 2 * x / (double) main->window_w - 1;
		camera = (t_camera){(t_vec) {cameraX, 0 }, (t_vec) { m->player->dir.x + m->player->plane.x * cameraX, m->player->dir.y + m->player->plane.y * cameraX}};
		m->pos = (t_point) {(int) m->player->pos.x, (int) m->player->pos.y};
		m->delta_dist.x = camera.ray.x == 0 ? INT_MAX : fabs(1 / camera.ray.x);
		m->delta_dist.y = camera.ray.y == 0 ? INT_MAX : fabs(1 / camera.ray.y);

		int stepX;
		int setpY;
		int hit = 0;
		int side;

		if (camera.ray.x < 0)
		{
			stepX = -1;
			m->side_dist.x = (m->player->pos.x - m->pos.x) * m->delta_dist.x;
		}
		else
		{
			stepX = 1;
			m->side_dist.x = (m->pos.x + 1.0 - m->player->pos.x) * m->delta_dist.x;
		}
	}
}
