/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 10:32:16 by pgorner           #+#    #+#             */
/*   Updated: 2023/04/14 15:08:00 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	msg_load_textures(mlx_texture_t **dest, char *path, int all)
{
	int		i;
	char	*tmp;
	char	*num;
	char	*cur_path;
	
	i = 0;
	while (i < all)
	{
		num = ft_itoa(i);
		tmp = ft_strjoin(path, num);
		cur_path = ft_strjoin(tmp, PNG);
		dest[i] = mlx_load_png(cur_path);
		free(cur_path);
		free(num);
		free(tmp);
		i++;
	}
}

void	msg_alloc_tex_im(t_m *m)
{
	int i;
	
	i = 0;
	m->men->msg->cubed = malloc(sizeof(mlx_texture_t) * m->men->msg->num_of_f);
	m->men->msg->start = malloc(sizeof(mlx_texture_t *) * 2);
	m->men->msg->maps = malloc(sizeof(mlx_texture_t *) * 2);
	m->men->msg->settings = malloc(sizeof(mlx_texture_t *) * 2);
	while (i < 2)
	{
		m->men->msg->start[i] = malloc(sizeof(mlx_texture_t *) * MSG_NOF);
		m->men->msg->maps[i] = malloc(sizeof(mlx_texture_t *) * MSG_NOF);
		m->men->msg->settings[i] = malloc(sizeof(mlx_texture_t *) * MSG_NOF);
		i++;
	}
}

void	draw_msg(t_m *m)
{
	msg_alloc_tex_im(m);
	msg_load_textures(m->men->msg->cubed, MSG_P, m->men->msg->num_of_f);
	msg_load_textures(m->men->msg->start[BLUE], MSG_STARTB, MSG_NOF);
	msg_load_textures(m->men->msg->start[GREEN], MSG_STARTG, MSG_NOF);
	msg_load_textures(m->men->msg->maps[BLUE], MSG_MAPSB, MSG_NOF);
	msg_load_textures(m->men->msg->maps[GREEN], MSG_MAPSG, MSG_NOF);
	msg_load_textures(m->men->msg->settings[BLUE], MSG_SETTINGSB, MSG_NOF);
	msg_load_textures(m->men->msg->settings[GREEN], MSG_SETTINGSG, MSG_NOF);
}
