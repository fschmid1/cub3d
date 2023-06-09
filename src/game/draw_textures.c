/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:38:01 by fschmid           #+#    #+#             */
/*   Updated: 2023/04/18 11:38:03 by fschmid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

static bool	should_draw(t_m *m, int tex, int tey, int height)
{
	return (((unsigned int)(tey * height + tex)
		<= (unsigned int)(m->tex[m->t->wall]->width
		* m->tex[m->t->wall]->height)) &&
					((unsigned int)(m->t->draw_start * m->window_w)
					+ m->x < m->map->img->width * m->map->img->height));
}

static void	draw_texture(t_m *m, int pos)
{
	if (m->t->is_door)
		ft_memcpy(&m->map->img->pixels[(m->t->draw_start
				* m->window_w + m->x) * 4],
			&m->tex[DOOR]->pixels[pos], 4);
	else
		ft_memcpy(&m->map->img->pixels[(m->t->draw_start
				* m->window_w + m->x) * 4],
			&m->tex[m->t->wall]->pixels[pos], 4);
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
		if (should_draw(m, tex, tey, height))
			draw_texture(m, (tey * height + tex) * 4);
		m->t->draw_start++;
	}
}
