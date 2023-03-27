/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 17:33:21 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/27 10:35:07 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_player	*setup_player(t_m *m)
{
	t_player	*player;
	char		dir;

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->pos = m->p->pos_p;
	dir = m->p->map[(int)m->p->pos_p.y][(int)m->p->pos_p.x];
	if (dir == 'W')
		player->dir = (t_vec) {-1, 0, 0};
	else if (dir == 'E')
		player->dir = (t_vec) {1, 0, 0};
	else if (dir == 'S')
		player->dir = (t_vec) {0, 1, 0};
	else if (dir == 'N')
		player->dir = (t_vec) {0, -1, 0};
	return (player);
}

t_camera	*setup_camera(t_m *m)
{
	t_camera *cam;
	char		dir;

	cam = malloc(sizeof(t_camera));
	cam->step = (t_vec){0.1, 0.1, 0};
	cam->old_plane = (t_vec){0, 0, 0};
	cam->plane = (t_vec){0, 0.66, 0};
	cam->side_dist = (t_vec){0, 0, 0};
	cam->delta_dist = (t_vec){0, 0, 0};
	cam->old_ray_dir = (t_vec){0, 0, 0};
	cam->side = 0;
	cam->perp_wd = 0;
	cam->hit = 0;
	cam->pos = (t_vec){m->p->pos_p.x, m->p->pos_p.y, 0};
	dir = m->p->map[(int)m->p->pos_p.x][(int)m->p->pos_p.y];
	if (dir == 'W')
		cam->ray_dir = (t_vec) {-1, 0, 0};
	else if (dir == 'E')
		cam->ray_dir = (t_vec) {1, 0, 0};
	else if (dir == 'S')
		cam->ray_dir = (t_vec) {0, 1, 0};
	else if (dir == 'N')
		cam->ray_dir = (t_vec) {-1, 0, 0};
	return (cam);
}
