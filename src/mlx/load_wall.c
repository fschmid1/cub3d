/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 18:04:43 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/26 18:11:06 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	load_wall(t_m *m)
{
	m->texim->no_tex = mlx_load_png(m->p->no);
	m->texim->so_tex = mlx_load_png(m->p->so);
	m->texim->we_tex = mlx_load_png(m->p->we);
	m->texim->ea_tex = mlx_load_png(m->p->ea);
	m->texim->no_img = mlx_texture_to_image(m->map->mlx, m->texim->no_tex);
	m->texim->so_img = mlx_texture_to_image(m->map->mlx, m->texim->so_tex);
	m->texim->we_img = mlx_texture_to_image(m->map->mlx, m->texim->we_tex);
	m->texim->ea_img = mlx_texture_to_image(m->map->mlx, m->texim->ea_tex);
}