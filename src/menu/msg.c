/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 10:32:16 by pgorner           #+#    #+#             */
/*   Updated: 2023/04/11 18:58:48 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	msg_load_textures(t_m *m, mlx_texture_t **dest, char *path)
{
	int		i;
	char	*tmp;
	char	*cur_path;
	
	i = 0;
	while (i < m->men->msg->num_of_f)
	{
		tmp = ft_strjoin(path, ft_itoa(i));
		cur_path = ft_strjoin(tmp, PNG);
		dest[i] = mlx_load_png(cur_path);
		free(cur_path);
		i++;
	}
}

void	msg_alloc_tex_im(t_m *m)
{
	int i;
	
	i = 0;
	m->men->msg->cubed = malloc(sizeof(mlx_texture_t) * m->men->msg->num_of_f);
	m->men->msg->start = malloc(sizeof(mlx_texture_t **) * 2);
	m->men->msg->maps = malloc(sizeof(mlx_texture_t *) * 2);
	m->men->msg->settings = malloc(sizeof(mlx_texture_t *) * 2);
	while (i < 2)
	{
		m->men->msg->start[i] = malloc(sizeof(mlx_texture_t) * MSG_NOF);
		m->men->msg->maps[i] = malloc(sizeof(mlx_texture_t) * MSG_NOF);
		m->men->msg->settings[i] = malloc(sizeof(mlx_texture_t) * MSG_NOF);
		i++;
	}

}

void	draw_msg(t_m *m)
{
	msg_alloc_tex_im(m);
	msg_load_textures(m, m->men->msg->cubed, MSG_P);
	msg_load_textures(m, m->men->msg->start[BLUE], MSG_STARTB);
	msg_load_textures(m, m->men->msg->start[GREEN], MSG_STARTG);
	msg_load_textures(m, m->men->msg->maps[BLUE], MSG_MAPSB);
	msg_load_textures(m, m->men->msg->maps[GREEN], MSG_MAPSG);
	msg_load_textures(m, m->men->msg->settings[BLUE], MSG_SETTINGSB);
	msg_load_textures(m, m->men->msg->settings[GREEN], MSG_SETTINGSG);
}
