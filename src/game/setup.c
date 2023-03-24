/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 17:33:21 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/24 17:34:02 by pgorner          ###   ########.fr       */
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
	player->pos_x = (double) m->pos_p.x;
	player->pos_y = (double) m->pos_p.y;
	player->plane_x = 0;
	player->plane_y = 0.66;
	dir = m->map[m->pos_p.x][m->pos_p.y];
	if (dir == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
	}
	else if (dir == 'O')
	{
		player->dir_x = 1;
		player->dir_y = 0;
	}
	else if (dir == 'S')
	{
		player->dir_x = 0;
		player->dir_y = -1;
	}
	else if (dir == 'N')
	{
		player->dir_x = 0;
		player->dir_y = 1;
	}
	return (player);
}
