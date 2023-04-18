/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:51:36 by pgorner           #+#    #+#             */
/*   Updated: 2023/04/18 12:16:49 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	mouse2(double mouse_movement, t_m *m, double ra)
{
	m->t->olddirx = m->t->dirx;
	m->t->dirx = m->t->dirx * cos(mouse_movement * ra)
		- m->t->diry * sin(mouse_movement * ra);
	m->t->diry = m->t->olddirx * sin(mouse_movement * ra)
		+ m->t->diry * cos(mouse_movement * ra);
	m->t->oldplanex = m->t->planex;
	m->t->planex = m->t->planex * cos(mouse_movement * ra)
		- m->t->planey * sin(mouse_movement * ra);
	m->t->planey = m->t->oldplanex * sin(mouse_movement * ra)
		+ m->t->planey * cos(mouse_movement * ra);
	m->x = 0;
}

void	mouse1(double mouse_movement, t_m *m, double ra)
{
	m->t->olddirx = m->t->dirx;
	m->t->dirx = m->t->dirx * cos(mouse_movement * ra)
		- m->t->diry * sin(mouse_movement * ra);
	m->t->diry = m->t->olddirx * sin(mouse_movement * ra)
		+ m->t->diry * cos(mouse_movement * ra);
	m->t->oldplanex = m->t->planex;
	m->t->planex = m->t->planex * cos(mouse_movement * ra)
		- m->t->planey * sin(mouse_movement * ra);
	m->t->planey = m->t->oldplanex * sin(mouse_movement * ra)
		+ m->t->planey * cos(mouse_movement * ra);
	m->x = 0;
}

void	mouse_hook(double x, double y, void *param)
{
	t_m		*m;
	double	ra;
	double	mouse_movement;

	(void) y;
	m = param;
	if (m->g_state != GAME)
		return ;
	mouse_movement = x - m->t->mouse.x;
	m->t->mouse.x = x;
	ra = 0.0174532925 * 0.075;
	if (mouse_movement > 0)
		mouse1(mouse_movement, m, ra);
	else if (mouse_movement < 0)
		mouse2(mouse_movement, m, ra);
}
