/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:11:31 by pgorner           #+#    #+#             */
/*   Updated: 2023/04/17 17:11:00 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	movement(t_m *m)
{
	m->t->old_time = m->t->time;
	m->t->time = mlx_get_time();
	m->t->frametime = (m->t->time - m->t->old_time) / 1000;
	m->t->movspeed = m->t->frametime * 5000;
	m->t->rotspeed = m->t->frametime * 3000;
	if (mlx_is_key_down(m->map->mlx, MLX_KEY_W))
	{
		if (m->t->map[(int)m->t->posy][(int)(m->t->posx + m->t->dirx * m->t->movspeed)] == WALKABLE || m->t->map[(int)m->t->posy][(int)(m->t->posx + m->t->dirx * m->t->movspeed)] == DOOR_OPEN)
			m->t->posx += m->t->dirx * m->t->movspeed;
		if (m->t->map[(int)(m->t->posy + m->t->diry * m->t->movspeed)][(int)(m->t->posx)] == WALKABLE || m->t->map[(int)(m->t->posy + m->t->diry * m->t->movspeed)][(int)(m->t->posx)] == DOOR_OPEN)
			m->t->posy += m->t->diry * m->t->movspeed;
		m->x = 0;
	}
	if (mlx_is_key_down(m->map->mlx, MLX_KEY_S))
	{
		if (m->t->map[(int)m->t->posy][(int)(m->t->posx - m->t->dirx * m->t->movspeed)] == WALKABLE || m->t->map[(int)m->t->posy][(int)(m->t->posx - m->t->dirx * m->t->movspeed)] == DOOR_OPEN)
			m->t->posx -= m->t->dirx * m->t->movspeed;
		if (m->t->map[(int)(m->t->posy - m->t->diry * m->t->movspeed)][(int)(m->t->posx)] == WALKABLE || m->t->map[(int)(m->t->posy - m->t->diry * m->t->movspeed)][(int)(m->t->posx)] == DOOR_OPEN)
			m->t->posy -= m->t->diry * m->t->movspeed;
		m->x = 0;
	}
	if (mlx_is_key_down(m->map->mlx, MLX_KEY_A))
	{
		if (m->t->map[(int)m->t->posy][(int)(m->t->posx - m->t->planex * m->t->movspeed)] == WALKABLE || m->t->map[(int)m->t->posy][(int)(m->t->posx - m->t->planex * m->t->movspeed)] == DOOR_OPEN)
			m->t->posx -= m->t->planex * m->t->movspeed;
		if (m->t->map[(int)(m->t->posy - m->t->planey * m->t->movspeed)][(int)(m->t->posx)] == WALKABLE || m->t->map[(int)(m->t->posy - m->t->planey * m->t->movspeed)][(int)(m->t->posx)] == DOOR_OPEN)
			m->t->posy -= m->t->planey * m->t->movspeed;
		m->x = 0;
	}
	if (mlx_is_key_down(m->map->mlx, MLX_KEY_D))
	{
		if (m->t->map[(int)m->t->posy][(int)(m->t->posx + m->t->planex * m->t->movspeed)] == WALKABLE || m->t->map[(int)m->t->posy][(int)(m->t->posx + m->t->planex * m->t->movspeed)] == DOOR_OPEN)
			m->t->posx += m->t->planex * m->t->movspeed;
		if (m->t->map[(int)(m->t->posy + m->t->planey * m->t->movspeed)][(int)(m->t->posx)] == WALKABLE || m->t->map[(int)(m->t->posy + m->t->planey * m->t->movspeed)][(int)(m->t->posx)] == DOOR_OPEN)
			m->t->posy += m->t->planey * m->t->movspeed;
		m->x = 0;
	}
	if (mlx_is_mouse_down(m->map->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		m->firing = 1;
		m->x = 0;
	}
	else
		m->firing = 0;
}

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
