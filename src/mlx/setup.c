/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:52:40 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/25 10:58:22 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <stdio.h>

t_m	*setup_main(void)
{
	t_m	*m;

	m = malloc(sizeof(t_m));
	m->window_h = 1080;
	m->window_w = 1920;
	m->p = setup_parse(m);
	m->map = setup_map(m);
	m->men = setup_menu();
	m->time = 0;
	m->old_time = 0;
	m->g_state = START;
	return (m);
}

t_p		*setup_parse(t_m *main)
{
	t_p	*m;

	m = malloc(sizeof(t_p));
	m->main = main;
	m->input = NULL;
	m->status = TRUE;
	m->pos_p.x = -1;
	m->pos_p.y = -1;
	m->fd = 0;
	m->file = NULL;
	m->map = NULL;
	m->fmap = NULL;
	m->input = NULL;
	m->no = NULL;
	m->so = NULL;
	m->we = NULL;
	m->ea = NULL;
	return (m);
}

t_map	*setup_map(t_m *m)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->mlx = NULL;
	map->img = NULL;
	map->csize = (t_vec) {0, 0};
	map->size = m->p->size;
	return (map);
}

t_menu	*setup_menu(void)
{
	t_menu	*menu;

	menu = malloc(sizeof(t_menu));
	if (!menu)
		return (NULL);
	menu->num_of_f = NUMOFFILES;
	menu->t = 0;
	menu->i = 0;
	menu->speed = SPEED;
	return (menu);
}

void	free_main(t_m *m)
{
	free(m->p->file);
	free_string_array(m->p->map);
	free_string_array(m->p->fmap);
	free_string_array(m->p->input);
	free(m->p->no);
	free(m->p->so);
	free(m->p->we);
	free(m->p->ea);
	free(m);
}
