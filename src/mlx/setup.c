/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:52:40 by pgorner           #+#    #+#             */
/*   Updated: 2023/04/17 17:36:51 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_m	*setup_main(void)
{
	t_m	*m;

	m = malloc(sizeof(t_m));
	m->window_h = 1080;
	m->window_w = 1920;
	m->p = setup_parse(m);
	m->map = setup_map();
	m->men = setup_menu();
	m->men->msg = setup_msg();
	m->time = 0;
	m->tex = NULL;
	m->t = NULL;
	m->old_time = 0;
	m->g_state = START;
	m->time = mlx_get_time();
	m->x = 0;
	m->selection = 0;
	m->firing = 0;
	return (m);
}

t_p	*setup_parse(t_m *main)
{
	t_p	*m;

	m = malloc(sizeof(t_p));
	m->main = main;
	m->input = NULL;
	m->status = TRUE;
	m->pos_p = (t_vec){-1, -1, 0};
	m->fd = 0;
	m->file = NULL;
	m->map = NULL;
	m->fmap = NULL;
	m->intmap = NULL;
	m->input = NULL;
	m->no = NULL;
	m->so = NULL;
	m->we = NULL;
	m->ea = NULL;
	return (m);
}

t_map	*setup_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->mlx = NULL;
	map->img = NULL;
	map->map = NULL;
	map->color = 0xFFFFFFFF;
	map->minmap_scale = 0;
	map->colorc = 0xa29a9aFF;
	map->colorf = 0x721818FF;
	map->fps = NULL;
	return (map);
}

t_msg	*setup_msg(void)
{
	t_msg	*msg;

	msg = malloc(sizeof(t_msg));
	if (!msg)
		return (NULL);
	msg->i = 1;
	msg->cubed = NULL;
	msg->start = NULL;
	msg->maps = NULL;
	msg->settings = NULL;
	return (msg);
}
