/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 18:04:43 by pgorner           #+#    #+#             */
/*   Updated: 2023/04/12 15:44:47 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	load_wall(t_m *m)
{
	m->tex = malloc(sizeof(mlx_texture_t *) * 4);
	m->tex[NO] = mlx_load_png(m->p->no);
	m->tex[SO] = mlx_load_png(m->p->so);
	m->tex[WE] = mlx_load_png(m->p->we);
	m->tex[EA] = mlx_load_png(m->p->ea);
	m->cross = malloc(sizeof(mlx_texture_t));
	m->cross = mlx_load_png("./textures/crosshair.png");
	m->gun = malloc(sizeof(mlx_texture_t));
	m->gun = mlx_load_png("./textures/gun2.png");
	m->muzzle = malloc(sizeof(mlx_texture_t));
	m->muzzle = mlx_load_png("./textures/muzzle.png");
}