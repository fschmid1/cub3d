/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_img.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 10:32:16 by pgorner           #+#    #+#             */
/*   Updated: 2023/04/11 16:01:25 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	load_textures(t_m *m, char *path)
{
	int		i;
	char	*tmp;
	char	*cur_path;
	
	i = 0;
	while (i < m->men->num_of_f)
	{
		tmp = ft_strjoin(path, ft_itoa(i));
		cur_path = ft_strjoin(tmp, PNG);
		m->men->tex[i] = mlx_load_png(cur_path);
		i++;
	}
}

void	tex_to_im(t_m *m)
{
	int	i;
	
	i = 0;
	while (i < m->men->num_of_f)
	{
		m->men->img[i]  = mlx_texture_to_image(m->map->mlx, m->men->tex[i]);
		i++;
	}
}

void	alloc_tex_im(t_m *m)
{
	m->men->tex = malloc(sizeof(mlx_texture_t) * m->men->num_of_f);
	m->men->img = malloc(sizeof(mlx_image_t) * m->men->num_of_f);
}

void	draw_menu(t_m *m)
{
	alloc_tex_im(m);
	load_textures(m, PATH);
	tex_to_im(m);
	// mlx_image_to_window(m->map->mlx, m->men->img[0], 0, 0);
}
