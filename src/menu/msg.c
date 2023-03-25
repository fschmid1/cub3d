/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 10:32:16 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/25 12:37:42 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	msg_load_textures(t_m *m, char *path)
{
	int		i;
	char	*tmp;
	char	*cur_path;
	
	i = 0;
	while (i < m->men->msg->num_of_f)
	{
		tmp = ft_strjoin(path, ft_itoa(i));
		cur_path = ft_strjoin(tmp, PNG);
		m->men->msg->tex[i] = mlx_load_png(cur_path);
		i++;
	}
}

void	msg_tex_to_im(t_m *m)
{
	int	i;
	
	i = 0;
	while (i < m->men->msg->num_of_f)
	{
		m->men->msg->img[i]  = mlx_texture_to_image(m->map->mlx, m->men->msg->tex[i]);
		i++;
	}
}

void	msg_alloc_tex_im(t_m *m)
{
	m->men->msg->tex = malloc(sizeof(mlx_texture_t) * m->men->msg->num_of_f);
	m->men->msg->img = malloc(sizeof(mlx_image_t) * m->men->msg->num_of_f);
}

void	draw_msg(t_m *m)
{
	msg_alloc_tex_im(m);
	msg_load_textures(m, MSG_P);
	msg_tex_to_im(m);
}
