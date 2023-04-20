/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:32:14 by fschmid           #+#    #+#             */
/*   Updated: 2023/04/20 14:08:41 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	rotate_handler_2(t_m *m)
{
	if (mlx_is_key_down(m->map->mlx, MLX_KEY_RIGHT))
	{
		m->t->olddirx = m->t->dirx;
		m->t->dirx = m->t->dirx * cos(m->t->rotspeed) - m->t->diry
			* sin(m->t->rotspeed);
		m->t->diry = m->t->olddirx * sin(m->t->rotspeed) + m->t->diry
			* cos(m->t->rotspeed);
		m->t->oldplanex = m->t->planex;
		m->t->planex = m->t->planex * cos(m->t->rotspeed) - m->t->planey
			* sin(m->t->rotspeed);
		m->t->planey = m->t->oldplanex * sin(m->t->rotspeed) + m->t->planey
			* cos(m->t->rotspeed);
		m->x = 0;
	}
}

void	rotate_handler(t_m *m)
{
	if (mlx_is_key_down(m->map->mlx, MLX_KEY_LEFT))
	{
		m->t->olddirx = m->t->dirx;
		m->t->dirx = m->t->dirx * cos(-m->t->rotspeed) - m->t->diry
			* sin(-m->t->rotspeed);
		m->t->diry = m->t->olddirx * sin(-m->t->rotspeed) + m->t->diry
			* cos(-m->t->rotspeed);
		m->t->oldplanex = m->t->planex;
		m->t->planex = m->t->planex * cos(-m->t->rotspeed) - m->t->planey
			* sin(-m->t->rotspeed);
		m->t->planey = m->t->oldplanex * sin(-m->t->rotspeed) + m->t->planey
			* cos(-m->t->rotspeed);
		m->x = 0;
	}
	rotate_handler_2(m);
}
