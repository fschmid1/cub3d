/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:16:34 by fschmid           #+#    #+#             */
/*   Updated: 2023/04/17 17:16:37 by fschmid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static bool	is_in_triangle(t_point p1, t_point p2, t_point p3, t_point p)
{
	double	ab;
	double	bc;
	double	ca;

	ab = (p2.y - p1.y) * (p.x - p1.x) - (p2.x - p1.x) * (p.y - p1.y);
	bc = (p3.y - p2.y) * (p.x - p2.x) - (p3.x - p2.x) * (p.y - p2.y);
	ca = (p1.y - p3.y) * (p.x - p3.x) - (p1.x - p3.x) * (p.y - p3.y);
	return ((ab >= 0 && bc >= 0 && ca >= 0) || (ab <= 0 && bc <= 0 && ca <= 0));
}

static void	draw_triangle_fill(t_m *m, t_triangle t, int color)
{
	t_point	p;

	p.y = t.min.y;
	while (p.y <= t.max.y)
	{
		p.x = t.min.x;
		while (p.x <= t.max.x)
		{
			if (is_in_triangle(t.p1, t.p2, t.p3, p))
				draw_pixel(m, p.x, p.y, color);
			p.x++;
		}
		p.y++;
	}
}

void	draw_triangle(t_m *m, t_point pos, int size, double dir)
{
	t_triangle	t;

	size /= 2;
	pos.x -= size;
	pos.y -= size;
	t.r = dir * M_PI / 180.0;
	t.p1 = (t_point){pos.x + size * cos(t.r), pos.y + size * sin(t.r)};
	t.p2 = (t_point){pos.x - size * cos(t.r + M_PI / 6),
		pos.y - size * sin(t.r + M_PI / 6)};
	t.p3 = (t_point){pos.x - size * cos(t.r - M_PI / 6),
		pos.y - size * sin(t.r - M_PI / 6)};
	t.min = (t_point){fmin(t.p1.x, fmin(t.p2.x, t.p3.x)),
		fmin(t.p1.y, fmin(t.p2.y, t.p3.y))};
	t.max = (t_point){fmax(t.p1.x, fmax(t.p2.x, t.p3.x)),
		fmax(t.p1.y, fmax(t.p2.y, t.p3.y))};
	draw_triangle_fill(m, t, 0xFF0000FF);
}
