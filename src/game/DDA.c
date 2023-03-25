/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DDA.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 15:06:07 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/25 16:20:57 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	dda(t_m *m)
{
	int line_height;
	int	draw_start;
	int	draw_end;

	while (m->map->hit == 0)
	{
		if (m->side_dist.x < m->side_dist.y)
		{
			m->side_dist.x += m->delta_dist.x;
			m->map->pos.x += m->map->step.x;
			m->map->side = 0;
		}
		else
		{
			m->side_dist.y += m->delta_dist.y;
			m->map->pos.y += m->map->step.y;
			m->map->side = 1;
		}
		if (m->p->map[m->map->pos.x][m->map->pos.y] > 0)
			m->map->hit = 1;
	}
}

void	calc_proj(t_m *m)
{
	if (m->map->side = 0)
		m->map->p_wall_dist = (m->side_dist.x - m->delta_dist.x)
	else
		m->map->p_wall_dist = (m->side_dist.y - m->delta_dist.y)
	
	line_height = (int)(m->window_h / m->p_wall_dist);
	
	draw_start = -line_height / 2 + m->window_h * 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + m->window_h / 2;
	if (draw_end >= m->window_h)
		draw_end = m->window_h - 1;
}

void	tex_calc_x(t_m *m)
{
	int	tex_num;
	int	tex_x;
	double	wall_x;

	tex_num = m->p->map[m->map->pos.x][m->map->pos.y] - 1;
	if (m->map->side == o)
		wall_x = m->map->player.x + m->p_wall_dist * m->camera->ray.y;
	else
		wall_x = m->map->player.x + m->p_wall_dist * m->camera->ray.x;
	wall_x -= floor((wall_x));
	
	tex_x = int (wall_x * double(m->map->tex_w));
	if (side == 0 && m->camera->ray.x > 0)
		tex_x = m->map->tex_w - tex_x - 1;
	if (side == 1 && m->camera->ray.y < 0)
		tex_x = m->map->tex_w - tex_x - 1;
}
