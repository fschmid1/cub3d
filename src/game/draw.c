/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:09:57 by pgorner           #+#    #+#             */
/*   Updated: 2023/04/17 17:36:04 by pgorner          ###   ########.fr       */
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
			draw_pixel(m, m->x, i, m->map->colorc);
		else if (i > m->t->draw_end)
			draw_pixel(m, m->x, i, m->map->colorf);
		i++;
	}
}

int	calc_tex(t_m *m)
{
	int		ret;
	double	wallx;

	ret = 0;
	if (m->t->wall == EA || m->t->wall == WE)
		wallx = (m->t->posy + m->t->pwd * m->t->raydiry);
	if (m->t->wall == SO || m->t->wall == NO)
		wallx = (m->t->posx + m->t->pwd * m->t->raydirx);
	wallx -= floor(wallx);
	ret = (int)(wallx * (double)(m->tex[m->t->wall]->width));
	if (m->t->wall == WE || m->t->wall == SO)
		ret = m->tex[m->t->wall]->width - ret - 1;
	return (ret);
}

void	draw_textures(t_m *m)
{
	double	offset;
	double	position;
	int		tex;
	int		tey;
	int		height;

	height = m->tex[m->t->wall]->height;
	offset = 1.00 * height / m->t->line_height;
	position = (m->t->draw_start
			- (m->window_h + m->t->line_height) / 2) * offset;
	tex = calc_tex(m);
	while (m->t->draw_start <= m->t->draw_end)
	{
		tey = (int)position + (height - 1);
		position += offset;
		if (((unsigned int)(tey * height + tex)
			<= (unsigned int)(m->tex[m->t->wall]->width
			* m->tex[m->t->wall]->height)) &&
			((unsigned int)(m->t->draw_start * m->window_w)
			+ m->x < m->map->img->width * m->map->img->height))
		{
			if (m->t->is_door)
				ft_memcpy(&m->map->img->pixels[(m->t->draw_start
						* m->window_w + m->x) * 4],
					&m->tex[DOOR]->pixels[(tey * height + tex) * 4], 4);
			else
				ft_memcpy(&m->map->img->pixels[(m->t->draw_start
						* m->window_w + m->x) * 4],
					&m->tex[m->t->wall]->pixels[(tey * height + tex) * 4],
					4);
		}
		m->t->draw_start++;
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
