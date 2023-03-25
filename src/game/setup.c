/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 17:33:21 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/24 19:30:10 by pgorner          ###   ########.fr       */
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
	player->pos = (t_vec) {m->p->pos_p.x, m->p->pos_p.y, 0};
	player->plane = (t_vec) {0, 0.66, 0};
	dir = m->p->map[m->p->pos_p.x][m->p->pos_p.y];
	if (dir == 'W')
		player->dir = (t_vec) {-1, 0, 0};
	else if (dir == 'O')
		player->dir = (t_vec) {1, 0, 0};
	else if (dir == 'S')
		player->dir = (t_vec) {0, -1, 0};
	else if (dir == 'N')
		player->dir = (t_vec) {0, 1, 0};
	return (player);
}
