/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:09:37 by pgorner           #+#    #+#             */
/*   Updated: 2023/04/17 17:16:51 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	set_values(t_m *m)
{
	m->t->camerax = 2 * m->x / (double)m->window_w - 1;
	m->t->raydirx = m->t->dirx + m->t->planex * m->t->camerax;
	m->t->raydiry = m->t->diry + m->t->planey * m->t->camerax;
	m->t->mapx = (int)m->t->posx;
	m->t->mapy = (int)m->t->posy;
}

void	delta_step(t_m *m)
{
	m->t->deltadistx = fabs(1 / m->t->raydirx);
	m->t->deltadisty = fabs(1 / m->t->raydiry);
	m->t->hit = 0;
	if (m->t->raydirx < 0)
	{
		m->t->stepx = -1;
		m->t->sidedistx = (m->t->posx - m->t->mapx) * m->t->deltadistx;
	}
	else
	{
		m->t->stepx = 1;
		m->t->sidedistx = (m->t->mapx + 1.0 - m->t->posx) * m->t->deltadistx;
	}
	if (m->t->raydiry < 0)
	{
		m->t->stepy = -1;
		m->t->sidedisty = (m->t->posy - m->t->mapy) * m->t->deltadisty;
	}
	else
	{
		m->t->stepy = 1;
		m->t->sidedisty = (m->t->mapy + 1.0 - m->t->posy) * m->t->deltadisty;
	}
}

void	set_side(t_m *m)
{
	if (m->t->sidedistx < m->t->sidedisty)
	{
		m->t->sidedistx += m->t->deltadistx;
		m->t->mapx += m->t->stepx;
		m->t->side = 0;
		m->t->wall = EA;
		if (m->t->raydirx < 0)
			m->t->wall = WE;
	}
	else
	{
		m->t->sidedisty += m->t->deltadisty;
		m->t->mapy += m->t->stepy;
		m->t->side = 1;
		m->t->wall = SO;
		if (m->t->raydiry < 0)
			m->t->wall = NO;
	}
}

void	dda(t_m *m)
{
	while (m->t->hit == 0)
	{
		set_side(m);
		if (m->t->map[m->t->mapy][m->t->mapx] > 0)
		{
			if (m->t->map[m->t->mapy][m->t->mapx] != DOOR_OPEN)
				m->t->hit = 1;
			if (m->t->map[m->t->mapy][m->t->mapx] == DOOR_CLOSED
				|| m->t->map[m->t->mapy][m->t->mapx] == DOOR_OPEN)
			{
				m->t->door_dist = m->t->pwd;
				m->t->door_pos = (t_point){m->t->mapx, m->t->mapy};
			}
			if (m->t->map[m->t->mapy][m->t->mapx] == DOOR_CLOSED)
				m->t->is_door = true;
			else
				m->t->is_door = false;
		}
	}
}

void	perp_wd(t_m *m)
{
	if (m->t->side == 0)
		m->t->pwd = (m->t->sidedistx - m->t->deltadistx);
	else
		m->t->pwd = (m->t->sidedisty - m->t->deltadisty);
}
