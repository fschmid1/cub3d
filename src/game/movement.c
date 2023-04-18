/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:46:34 by fschmid           #+#    #+#             */
/*   Updated: 2023/04/18 11:46:36 by fschmid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	movement_down(t_m *m)
{
	if (mlx_is_key_down(m->map->mlx, MLX_KEY_S))
	{
		if (m->t->map[(int)m->t->posy][(int)(m->t->posx - m->t->dirx
			* m->t->movspeed)] == WALKABLE
			|| m->t->map[(int)m->t->posy][(int)(m->t->posx - m->t->dirx
				* m->t->movspeed)] == DOOR_OPEN)
			m->t->posx -= m->t->dirx * m->t->movspeed;
		if (m->t->map[(int)(m->t->posy - m->t->diry
				* m->t->movspeed)][(int)(m->t->posx)] == WALKABLE
			|| m->t->map[(int)(m->t->posy - m->t->diry
				* m->t->movspeed)][(int)(m->t->posx)] == DOOR_OPEN)
			m->t->posy -= m->t->diry * m->t->movspeed;
		m->x = 0;
	}
}

static void	movement_up(t_m *m)
{
	if (mlx_is_key_down(m->map->mlx, MLX_KEY_W))
	{
		if (m->t->map[(int)m->t->posy][(int)(m->t->posx + m->t->dirx
			* m->t->movspeed)] == WALKABLE
			|| m->t->map[(int)m->t->posy][(int)(m->t->posx + m->t->dirx
				* m->t->movspeed)] == DOOR_OPEN)
			m->t->posx += m->t->dirx * m->t->movspeed;
		if (m->t->map[(int)(m->t->posy + m->t->diry
				* m->t->movspeed)][(int)(m->t->posx)] == WALKABLE
			|| m->t->map[(int)(m->t->posy + m->t->diry
				* m->t->movspeed)][(int)(m->t->posx)] == DOOR_OPEN)
			m->t->posy += m->t->diry * m->t->movspeed;
		m->x = 0;
	}
}

static void	movement_left(t_m *m)
{
	if (mlx_is_key_down(m->map->mlx, MLX_KEY_A))
	{
		if (m->t->map[(int)m->t->posy][(int)(m->t->posx - m->t->planex
			* m->t->movspeed)] == WALKABLE ||
				m->t->map[(int)m->t->posy][(int)(m->t->posx
					- m->t->planex * m->t->movspeed)] == DOOR_OPEN)
			m->t->posx -= m->t->planex * m->t->movspeed;
		if (m->t->map[(int)(m->t->posy - m->t->planey
				* m->t->movspeed)][(int)(m->t->posx)] == WALKABLE
				|| m->t->map[(int)(m->t->posy - m->t->planey
					* m->t->movspeed)][(int)(m->t->posx)] == DOOR_OPEN)
			m->t->posy -= m->t->planey * m->t->movspeed;
		m->x = 0;
	}
}

static void	movement_right(t_m *m)
{
	if (mlx_is_key_down(m->map->mlx, MLX_KEY_D))
	{
		if (m->t->map[(int)m->t->posy][(int)(m->t->posx + m->t->planex
			* m->t->movspeed)] == WALKABLE ||
		m->t->map[(int)m->t->posy][(int)(m->t->posx
		+ m->t->planex * m->t->movspeed)] == DOOR_OPEN)
			m->t->posx += m->t->planex * m->t->movspeed;
		if (m->t->map[(int)(m->t->posy + m->t->planey
				* m->t->movspeed)][(int)(m->t->posx)] == WALKABLE
		|| m->t->map[(int)(m->t->posy + m->t->planey
		* m->t->movspeed)][(int)(m->t->posx)] == DOOR_OPEN)
			m->t->posy += m->t->planey * m->t->movspeed;
		m->x = 0;
	}
}

void	movement(t_m *m)
{
	m->t->old_time = m->t->time;
	m->t->time = mlx_get_time();
	m->t->frametime = (m->t->time - m->t->old_time) / 1000;
	m->t->movspeed = m->t->frametime * 5000;
	m->t->rotspeed = m->t->frametime * 3000;
	movement_up(m);
	movement_down(m);
	movement_left(m);
	movement_right(m);
	if (mlx_is_mouse_down(m->map->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		m->firing = 1;
		m->x = 0;
	}
	else
		m->firing = 0;
}
