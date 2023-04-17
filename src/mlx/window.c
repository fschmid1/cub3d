/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:53:00 by pgorner           #+#    #+#             */
/*   Updated: 2023/04/14 17:50:01 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	setup_window(t_m *m)
{
	m->map->mlx = mlx_init(m->window_w, m->window_h, "cub3D", true);
	if (!m->map->mlx)
		return (puts(mlx_strerror(mlx_errno)), EXIT_FAILURE);
	m->map->img = mlx_new_image(m->map->mlx, m->window_w, m->window_h);
	if (!m->map->img)
		return (mlx_close_window(m->map->mlx),
			puts(mlx_strerror(mlx_errno)), EXIT_FAILURE);
	if (mlx_image_to_window(m->map->mlx, m->map->img, 0, 0) == -1)
		return (mlx_close_window(m->map->mlx),
			puts(mlx_strerror(mlx_errno)), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	make_cubed(t_m *m)
{
	unsigned int i;
	unsigned int c;
	int pos = m->window_h / 2 * m->window_w / 2 + 19860;

	i = 0;
	c = 0;
	while (i++ < (m->men->msg->cubed[m->men->msg->i]->width
		* m->men->msg->cubed[m->men->msg->i]->height))
	{
		if (c == m->men->msg->cubed[m->men->msg->i]->width)
		{
			c = 0;
			pos += m->men->tex[0]->width - m->men->msg->cubed[m->men->msg->i]->width;
		}
		c++;
		if(m->men->msg->cubed[m->men->msg->i]->pixels[(i) * 4] != 0)
			ft_memcpy(&m->map->img->pixels[(i + pos) * 4],
				&m->men->msg->cubed[m->men->msg->i]->pixels[(i) * 4], 4);
	}
}

void	make_start(t_m *m)
{
	unsigned int i;
	unsigned int c;
	int pos;
	int color;

	i = 0;
	c = 0;
	pos = m->window_h / 2 * m->window_w / 1.5 + 46865;
	if (m->selection == 0)
		color = GREEN;
	else
		color = BLUE;
	while (i++ < (m->men->msg->start[color][m->men->msg->i]->width
		* m->men->msg->start[color][m->men->msg->i]->height))
	{
		if (c == m->men->msg->start[color][m->men->msg->i]->width)
		{
			c = 0;
			pos += m->men->tex[0]->width - m->men->msg->start[color][m->men->msg->i]->width;
		}
		c++;
		if(m->men->msg->start[color][m->men->msg->i]->pixels[(i) * 4] != 0)
			ft_memcpy(&m->map->img->pixels[(i + pos) * 4],
				&m->men->msg->start[color][m->men->msg->i]->pixels[(i) * 4], 4);
	}
}
void	make_maps(t_m *m)
{
	unsigned int i;
	unsigned int c;
	int pos = m->window_h / 2 * m->window_w / 1.3 + 46150;
	int color = 0;

	if (m->selection == 1)
		color = GREEN;
	else
		color = BLUE;
	i = 0;
	c = 0;
	while (i++ < (m->men->msg->maps[color][m->men->msg->i]->width
		* m->men->msg->maps[color][m->men->msg->i]->height))
	{
		if (c == m->men->msg->maps[color][m->men->msg->i]->width)
		{
			c = 0;
			pos += m->men->tex[0]->width - m->men->msg->maps[color][m->men->msg->i]->width;
		}
		c++;
		if(m->men->msg->maps[color][m->men->msg->i]->pixels[(i) * 4] != 0)
			ft_memcpy(&m->map->img->pixels[(i + pos) * 4],
				&m->men->msg->maps[color][m->men->msg->i]->pixels[(i) * 4], 4);
	}
}

void	make_settings(t_m *m)
{
	unsigned int i;
	unsigned int c;
	int pos = m->window_h / 2 * m->window_w / 1.15 + 49567;
	int color = 0;

	if (m->selection == 2)
		color = GREEN;
	else
		color = BLUE;
	i = 0;
	c = 0;
	while (i++ < (m->men->msg->settings[color][m->men->msg->i]->width
		* m->men->msg->settings[color][m->men->msg->i]->height))
	{
		if (c == m->men->msg->settings[color][m->men->msg->i]->width)
		{
			c = 0;
			pos += m->men->tex[0]->width - m->men->msg->settings[color][m->men->msg->i]->width;
		}
		c++;
		if(m->men->msg->settings[color][m->men->msg->i]->pixels[(i) * 4] != 0)
			ft_memcpy(&m->map->img->pixels[(i + pos) * 4],
				&m->men->msg->settings[color][m->men->msg->i]->pixels[(i) * 4], 4);
	}
}

void	key(mlx_key_data_t keydata, void *param)
{
	t_m	*m;
	m = param;

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
		{
			// draw_menu(m);
			m->g_state = START;
		}
		else
			mlx_close_window(m->map->mlx);
	}
	if (keydata.key == MLX_KEY_ENTER && keydata.action == MLX_PRESS
		&& m->selection == 0)
		{
			m->g_state = GAME;
			// close_menu(m);
			mlx_image_to_window(m->map->mlx, m->map->img, 0, 0);
		}
	if (keydata.key == MLX_KEY_ENTER && keydata.action == MLX_PRESS
		&& m->selection == 1)
		m->g_state = MAPS;
	if (keydata.key == MLX_KEY_ENTER && keydata.action == MLX_PRESS
		&& m->selection == 2)
		m->g_state = SETTINGS;
}

void	draw_image(t_m *m)
{
	unsigned int i;

	i = 0;
	while (i++ < (1920*1080 - 1))
	{
		ft_memcpy(&m->map->img->pixels[(i) * 4],
			&m->men->tex[m->men->i]->pixels[i * 4], 4);
	}
}

void	menu_hook(void *param)
{
	t_m	*m;
	m = param;
	double	time;

	time = mlx_get_time();
	mlx_key_hook(m->map->mlx, key, m);
	if (time - m->men->t > m->men->speed && m->g_state == START)
	{
		ft_memset(m->map->img->pixels, 0,
			m->window_w * m->window_h * sizeof(int32_t));
		if (m->men->i < m->men->num_of_f - 1)
			m->men->i++;
		else
			m->men->i = 0;
		if (m->men->msg->i < m->men->msg->num_of_f - 1)
			m->men->msg->i++;
		else
			m->men->msg->i = 0;
		printf("m->men->i %i\n", m->men->i);
		draw_image(m);
		make_start(m);
		make_maps(m);
		make_cubed(m);
		make_settings(m);
		m->men->t = time;
	}
	if (m->g_state == GAME)
		game_loop(m);
}

void	mouse_hook(double x, double y, void *param)
{
	t_m	*m;
	double	ra;
	double	mouse_movement;

	(void) y;
	m = param;
	if (m->g_state != GAME)
		return ;
	mouse_movement = x - m->t->mouse.x;
    m->t->mouse.x = x;
	ra = 0.0174532925 * 0.075;
    if (mouse_movement > 0) // mouse moved right
    {
        m->t->olddirx = m->t->dirx;
        m->t->dirx = m->t->dirx * cos(mouse_movement * ra) - m->t->diry * sin(mouse_movement * ra);
        m->t->diry = m->t->olddirx * sin(mouse_movement * ra) + m->t->diry * cos(mouse_movement * ra);
        m->t->oldplanex = m->t->planex;
        m->t->planex = m->t->planex * cos(mouse_movement * ra) - m->t->planey * sin(mouse_movement * ra);
        m->t->planey = m->t->oldplanex * sin(mouse_movement * ra) + m->t->planey * cos(mouse_movement * ra);
        m->x = 0;
    }
    else if (mouse_movement < 0) // mouse moved left
    {
        m->t->olddirx = m->t->dirx;
        m->t->dirx = m->t->dirx * cos(mouse_movement * ra) - m->t->diry * sin(mouse_movement * ra);
        m->t->diry = m->t->olddirx * sin(mouse_movement * ra) + m->t->diry * cos(mouse_movement * ra);
        m->t->oldplanex = m->t->planex;
        m->t->planex = m->t->planex * cos(mouse_movement * ra) - m->t->planey * sin(mouse_movement * ra);
        m->t->planey = m->t->oldplanex * sin(mouse_movement * ra) + m->t->planey * cos(mouse_movement * ra);
        m->x = 0;
    }
}

void	register_hooks(t_m *m)
{
	mlx_loop_hook(m->map->mlx, &menu_hook, m);
	mlx_cursor_hook(m->map->mlx, &mouse_hook, m);
	mlx_set_cursor_mode(m->map->mlx, MLX_MOUSE_DISABLED);
}
