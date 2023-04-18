/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:53:00 by pgorner           #+#    #+#             */
/*   Updated: 2023/04/18 11:51:30 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	keydata1(mlx_key_data_t keydata, t_m *m)
{
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS
		&& m->g_state == START)
	{
		if (m->selection == 0)
			m->selection = 2;
		else
			m->selection -= 1;
	}
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS
		&& m->g_state == START)
	{
		if (m->selection == 2)
			m->selection = 0;
		else
			m->selection += 1;
	}
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		if (m->g_state == GAME)
			m->g_state = START;
		else
			mlx_close_window(m->map->mlx);
	}
}

void	key(mlx_key_data_t keydata, void *param)
{
	t_m	*m;

	m = param;
	keydata1(keydata, m);
	if (keydata.key == MLX_KEY_ENTER && keydata.action == MLX_PRESS
		&& m->selection == 0)
	{
		m->g_state = GAME;
		mlx_image_to_window(m->map->mlx, m->map->img, 0, 0);
	}
	if (keydata.key == MLX_KEY_ENTER && keydata.action == MLX_PRESS
		&& m->selection == 1)
		m->g_state = MAPS;
	if (keydata.key == MLX_KEY_ENTER && keydata.action == MLX_PRESS
		&& m->selection == 2)
		m->g_state = SETTINGS;
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS
		&& m->g_state == GAME && m->t->door_dist < 1.5)
	{
		if (m->t->map[m->t->door_pos.y][m->t->door_pos.x] == DOOR_CLOSED)
			m->t->map[m->t->door_pos.y][m->t->door_pos.x] = DOOR_OPEN;
		else if (m->t->map[m->t->door_pos.y][m->t->door_pos.x] == DOOR_OPEN)
			m->t->map[m->t->door_pos.y][m->t->door_pos.x] = DOOR_CLOSED;
		m->x = 0;
	}
}

void	draw_image(t_m *m)
{
	unsigned int	i;

	i = 0;
	while (i++ < (unsigned int)(m->window_h * m->window_w - 1))
	{
		ft_memcpy(&m->map->img->pixels[(i) * 4],
			&m->men->tex[m->men->i]->pixels[i * 4], 4);
	}
}

void	menu_hook(void *param)
{
	t_m		*m;
	double	time;

	m = param;
	time = mlx_get_time();
	mlx_key_hook(m->map->mlx, key, m);
	if (time - m->men->t > m->men->speed && m->g_state == START)
	{
		ft_memset(m->map->img->pixels, 0,
			m->window_w * m->window_h * sizeof(int32_t));
		if (m->men->i < NUMOFFILES)
			m->men->i++;
		else
			m->men->i = 0;
		if (m->men->msg->i < MSG_NOF)
			m->men->msg->i++;
		else
			m->men->msg->i = 2;
		draw_image(m);
		make_cubed(m);
		m->men->t = time;
	}
	if (m->g_state == GAME)
		game_loop(m);
}

void	register_hooks(t_m *m)
{
	mlx_loop_hook(m->map->mlx, &menu_hook, m);
	mlx_cursor_hook(m->map->mlx, &mouse_hook, m);
	mlx_set_cursor_mode(m->map->mlx, MLX_MOUSE_DISABLED);
}
