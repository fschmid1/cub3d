/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:11:31 by pgorner           #+#    #+#             */
/*   Updated: 2023/04/17 18:07:05 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	muzzle(t_m *m)
{
	int				pos;
	unsigned int	i;
	unsigned int	c;

	i = 0;
	c = 0;
	pos = m->window_h / 2 * m->window_w / 1.21 + 115;
	while (i++ < (m->muzzle->width * m->muzzle->height))
	{
		if (c == m->muzzle->width)
		{
			c = 0;
			pos += m->men->tex[0]->width - m->muzzle->width;
		}
		c++;
		if (m->muzzle->pixels[(i) * 4] != 0)
		{
			ft_memcpy(&m->map->img->pixels[(pos + i) * 4],
				&m->muzzle->pixels[(i) * 4], 4);
		}
	}
}

static void	draw_gun(t_m *m, int pos, unsigned int x, unsigned int y)
{
	while (y < m->gun->height)
	{
		x = 0;
		while (x < m->gun->width)
		{
			if ((m->gun->pixels[(y * m->gun->width + x) * 4] != 0)
				&& (pos + y * m->men->tex[0]->width + x)
				< (unsigned int)(m->window_h * m->window_w))
			{
				ft_memcpy(&m->map->img->pixels[(pos + y
						* m->men->tex[0]->width + x) * 4],
					&m->gun->pixels[(y * m->gun->width + x) * 4], 4);
			}
			x++;
		}
		y++;
	}
}

void	gun(t_m *m)
{
	unsigned int	x;
	unsigned int	y;
	int				pos;

	x = 0;
	y = 0;
	pos = m->window_h / 1.7 * m->window_w / 1.2 - 100;
	if (m->firing == 1)
		muzzle(m);
	draw_gun(m, pos, x, y);
	if (m->firing == 1)
	{
		m->firing = 0;
		m->x = 0;
	}
}

void	fps_counter(t_m *m)
{
	char	*fps;
	char	*num;

	mlx_delete_image(m->map->mlx, m->map->fps);
	num = ft_itoa((int)((1.0 / (m->t->frametime * 1000))));
	fps = ft_strjoin("FPS ", num);
		m->map->fps = mlx_put_string(m->map->mlx, fps, 1800, 50);
	free(num);
	free(fps);
}

void	game_loop(void *param)
{
	t_m	*m;

	m = param;
	movement(m);
	if (m->x == 0)
	{
		ft_memset(m->map->img->pixels, 0,
			m->window_w * m->window_h * sizeof(int32_t));
	}
	while (m->x <= m->window_w)
	{
		set_values(m);
		delta_step(m);
		dda(m);
		perp_wd(m);
		draw_lines(m);
		m->x++;
	}
	gun(m);
	fps_counter(m);
	minimap(m);
}
