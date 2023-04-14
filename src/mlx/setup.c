/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:52:40 by pgorner           #+#    #+#             */
/*   Updated: 2023/04/12 15:43:54 by pgorner          ###   ########.fr       */
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
	m->map = setup_map();
	m->men = setup_menu();
	m->men->msg = setup_msg();
	m->time = 0;
	m->old_time = 0;
	m->g_state = START;
	m->time = mlx_get_time();
	m->x = 0;
	m->selection = 0;
	m->firing = 0;
	return (m);
}

t_p		*setup_parse(t_m *main)
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
	msg->num_of_f = MSG_NOF;
	msg->i = 0;
	return (msg);
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

void	free_parse(t_m *m)
{
	int i = 0;
	while (i < m->p->size.x)
	{
		// while(j < m->p->size.x)
		// {
			free(m->p->intmap[i++]);
		// }
	}
	free(m->p);
}

void	free_msg(t_m *m)
{
	int i;
	int j;

	i = 0;
	while (i < m->men->msg->num_of_f)
	{
		free(m->men->tex[i]);
		free(m->men->msg->cubed[i++]);
	}
	free(m->men->tex);
	free(m->men->img);
	free(m->men->msg->cubed);
    // Free start, maps, and settings arrays
	while (i <= 2)
	{
		j =0 ;
		while (j < MSG_NOF)
		{
        	free(m->men->msg->start[i][j]);
        	free(m->men->msg->maps[i][j]);
        	free(m->men->msg->settings[i][j++]);
		}
        free(m->men->msg->start[i]);
        free(m->men->msg->maps[i]);
        free(m->men->msg->settings[i++]);
    }
    // Free start, maps, and settings pointers
    free(m->men->msg->start);
    free(m->men->msg->maps);
    free(m->men->msg->settings);
	free(m->men->msg);
	free(m->men);

}

void	free_main(t_m *m)
{
	free(m->p->file);
	free_string_array(m->p->map);
	free_string_array(m->p->fmap);
	free_string_array(m->p->input);
	mlx_delete_image(m->map->mlx, m->map->fps);
	mlx_delete_image(m->map->mlx, m->map->img);
	free(m->p->no);
	free(m->p->so);
	free(m->p->we);
	free(m->p->ea);
	free(m->t->map);
	free_msg(m);
	free_parse(m);
	free(m);
}
