/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:03:49 by pgorner           #+#    #+#             */
/*   Updated: 2023/04/17 17:31:37 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
	int	i;
	int	j;

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
	return (free(m->men->msg->start), free(m->men->msg->maps),
		free(m->men->msg->settings), free(m->men->msg));
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
	int	i;

	i = 0;
	if (!m->men)
		return ;
	free_msg(m);
	while (m->men->tex && i <= NUMOFFILES)
		mlx_delete_texture(m->men->tex[i++]);
	free(m->men->tex);
	free(m->men);
}
