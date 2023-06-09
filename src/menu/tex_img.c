/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_img.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 10:32:16 by pgorner           #+#    #+#             */
/*   Updated: 2023/04/17 15:26:03 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	load_textures(t_m *m, char *path)
{
	int		i;
	char	*tmp;
	char	*num;
	char	*cur_path;

	i = 0;
	while (i <= NUMOFFILES)
	{
		num = ft_itoa(i);
		tmp = ft_strjoin(path, num);
		free(num);
		cur_path = ft_strjoin(tmp, PNG);
		free(tmp);
		m->men->tex[i] = mlx_load_png(cur_path);
		free(cur_path);
		i++;
	}
}

void	alloc_tex_im(t_m *m)
{
	m->men->tex = malloc(sizeof(mlx_texture_t *) * NUMOFFILES);
}
