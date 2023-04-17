/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:16:25 by fschmid           #+#    #+#             */
/*   Updated: 2023/04/17 17:16:30 by fschmid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	draw_square(t_m *m, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < m->map->minmap_scale)
	{
		j = 0;
		while (j < m->map->minmap_scale)
		{
			draw_pixel(m, x + i + 20, y + j + 20, color);
			j++;
		}
		i++;
	}
}

static double	to_angle(t_m *m)
{
	double	radians;
	double	degrees;

	radians = atan2(m->t->diry, m->t->dirx);
	degrees = radians * 180.0 / M_PI;
	return (degrees);
}

static void	draw_player(t_m *m)
{
	int	mh;
	int	mw;
	int	rh;
	int	rw;

	mh = m->map->minmap_scale * m->p->size.y;
	mw = m->map->minmap_scale * m->p->size.x;
	rh = mh / m->p->size.y;
	rw = mw / m->p->size.x;
	draw_triangle(m, (t_point){(m->t->posx * rw) + m->map->minmap_scale + 20,
		(m->t->posy * rh) + m->map->minmap_scale + 20}, 10, to_angle(m));
}

void	minimap(t_m	*m)
{
	t_point	i;
	t_point	p;

	i.x = 0;
	p = (t_point){0, 0};
	m->map->minmap_scale = 200 / m->p->size.x;
	while (i.x < m->p->size.y)
	{
		i.y = 0;
		while (i.y < m->p->size.x)
		{
			if (m->p->map[i.x][i.y] == '1')
				draw_square(m, p.x, p.y, m->map->color);
			else if (m->p->map[i.x][i.y] == '0'
					|| ft_strchr("WESN", m->p->map[i.x][i.y]))
				draw_square(m, p.x, p.y, m->map->colorf);
			i.y++;
			p.x += m->map->minmap_scale;
		}
		i.x++;
		p.x = 0;
		p.y += m->map->minmap_scale;
	}
	draw_player(m);
}
