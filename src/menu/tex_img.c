/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_img.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 10:32:16 by pgorner           #+#    #+#             */
/*   Updated: 2023/04/14 17:41:41 by pgorner          ###   ########.fr       */
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
	while (i < m->men->num_of_f)
	{
		num = ft_itoa(i);
		tmp = ft_strjoin(path, num);
		cur_path = ft_strjoin(tmp, PNG);
		m->men->tex[i] = mlx_load_png(cur_path);
		free(num);
		free(tmp);
		free(cur_path);
		i++;
	}
}


void	alloc_tex_im(t_m *m)
{
	m->men->tex = malloc(sizeof(mlx_texture_t *) * m->men->num_of_f);
}

// void	close_menu(t_m *m)
// {
// 	int	i;
	
// 	i = 0;
// 	while (i < m->men->num_of_f)
// 	{
// 		mlx_delete_image(m->map->mlx, m->men->img[i]);
// 		i++;
// 	}
// }
