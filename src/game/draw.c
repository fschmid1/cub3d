/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:09:57 by pgorner           #+#    #+#             */
/*   Updated: 2023/04/18 13:32:05 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_ceiling(t_m *m)
{
	int	i;

	i = 0;
	while (i < m->window_h)
	{
		if (i < m->t->draw_start)
			draw_pixel(m, m->x, i, m->p->c);
		else if (i > m->t->draw_end)
			draw_pixel(m, m->x, i, m->p->f);
		i++;
	}
}

void	draw_lines(t_m *m)
{
	m->t->line_height = (int)(m->window_h / m->t->pwd);
	m->t->draw_start = -m->t->line_height / 2 + m->window_h / 2;
	m->t->draw_end = m->t->line_height / 2 + m->window_h / 2;
	if (m->t->draw_start < 0)
		m->t->draw_start = 0;
	if (m->t->draw_end >= m->window_h)
		m->t->draw_end = m->window_h - 1;
	draw_ceiling(m);
	draw_textures(m);
}
