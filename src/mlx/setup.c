/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:52:40 by pgorner           #+#    #+#             */
/*   Updated: 2023/04/17 15:58:33 by fschmid          ###   ########.fr       */
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
	msg->i = 0;
	msg->cubed = NULL;
	msg->start = NULL;
	msg->maps = NULL;
	msg->settings = NULL;
	return (msg);
}

t_menu	*setup_menu(void)
{
	t_menu	*menu;

	menu = malloc(sizeof(t_menu));
	if (!menu)
		return (NULL);
	menu->t = 0;
	menu->i = 0;
	menu->speed = SPEED;
	menu->tex = NULL;
	menu->msg = NULL;
	return (menu);
}

void	free_parse(t_m *m)
{
	int	i;

	i = 0;
	free(m->p->no);
	free(m->p->so);
	free(m->p->we);
	free(m->p->ea);
	while (m->p->intmap && i < m->p->size.y)
		free(m->p->intmap[i++]);
	if (m->p->intmap)
		free(m->p->intmap);
	free(m->p);
}

void	free_msg(t_m *m)
{
	int i;
	int j;

	i = 0;
	if (!m->men || !m->men->msg)
		return ;
	while (m->men->msg->cubed && i <= MSG_NOF)
		mlx_delete_texture(m->men->msg->cubed[i++]);
	free(m->men->msg->cubed);
	i = 0;
	while (m->men->msg->cubed && i < 2)
	{
		j = 0;
		while (j <= MSG_NOF)
		{
        	mlx_delete_texture(m->men->msg->start[i][j]);
        	mlx_delete_texture(m->men->msg->maps[i][j]);
        	mlx_delete_texture(m->men->msg->settings[i][j++]);
		}
        free(m->men->msg->start[i]);
        free(m->men->msg->maps[i]);
        free(m->men->msg->settings[i++]);
    }
	return (free(m->men->msg->start), free(m->men->msg->maps), free(m->men->msg->settings),
				free(m->men->msg));
}


void	free_load_wall(t_m *m)
{
	if (!m->tex)
		return ;
	mlx_delete_texture(m->tex[NO]);
	mlx_delete_texture(m->tex[SO]);
	mlx_delete_texture(m->tex[WE]);
	mlx_delete_texture(m->tex[EA]);
	mlx_delete_texture(m->tex[DOOR]);
	free(m->tex);
	mlx_delete_texture(m->cross);
	mlx_delete_texture(m->gun);
	mlx_delete_texture(m->muzzle);
}

void	free_map(t_m *m)
{
	int	i;

	i = 0;
	while (m->map->map && i < m->p->size.y)
	{
		free(m->map->map[i]);
		free(m->t->map[i++]);
	}
	if (m->map->map)
	{
		free(m->map->map);
		free(m->t->map);
	}
	free(m->map);
}

void	free_menu(t_m *m)
{
	int i;

	i = 0;
	if (!m->men)
		return ;
	free_msg(m);
	while (m->men->tex && i <= NUMOFFILES)
		mlx_delete_texture(m->men->tex[i++]);
	free(m->men->tex);
	free(m->men);
}

void	free_main(t_m *m)
{
	free(m->p->file);
	free_string_array(m->p->map);
	free_string_array(m->p->fmap);
	free_string_array(m->p->input);
	if (m->map->mlx)
	{
		mlx_delete_image(m->map->mlx, m->map->fps);
		mlx_delete_image(m->map->mlx, m->map->img);
	}
	free_map(m);
	free_load_wall(m);
	free_parse(m);
	free_menu(m);
	free(m->t);

	free(m);
}
