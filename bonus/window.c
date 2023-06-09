/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:53:00 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/25 14:53:56 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	setup_window(t_m *m)
{
	m->map->mlx = mlx_init(m->window_w, m->window_h, "cub3d", true);
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

void	main_hooks(void *param)
{
	t_m	*m;

	m = param;
	if (mlx_is_key_down(m->map->mlx, MLX_KEY_ESCAPE) 
		&& m->g_state == MENU)
	{
		m->g_state = PAUSE;
		mlx_put_string(m->map->mlx, "DO YOU WANT TO QUIT?", 700, MSG_H);
		mlx_put_string(m->map->mlx, "PRESS SPACE TO EXIT OR", 700, MSG_H + 20);
		mlx_put_string(m->map->mlx, "ENTER TO CONTINUE", 700, MSG_H + 40);
		m->g_state = EXIT;
	}
	if (mlx_is_key_down(m->map->mlx, MLX_KEY_SPACE)
		&& m->g_state == EXIT)
		mlx_close_window(m->map->mlx);
	if (mlx_is_key_down(m->map->mlx, MLX_KEY_ENTER)
		&& m->g_state == EXIT)
			m->g_state = MENU;
	if (mlx_is_key_down(m->map->mlx, MLX_KEY_ESCAPE)
		&& m->g_state != MENU && m->g_state != EXIT)
		{
			m->prev_state = m->g_state;
			m->g_state = PAUSE;
		}
	if (mlx_is_key_down(m->map->mlx, MLX_KEY_ESCAPE)
		&& m->g_state == PAUSE && m->g_state != EXIT)
			m->g_state = m->prev_state;
}

void	menu_hook(void *param)
{
	t_m	*m;
	m = param;
	double	time;
	
	time = mlx_get_time();
	if (time - m->men->t > m->men->speed && m->g_state == MENU)
	{
		if (m->men->i < m->men->num_of_f - 1)
			m->men->i++;
		else
			m->men->i = 0;
		mlx_image_to_window(m->map->mlx, m->men->img[m->men->i], 0, 0);
		m->men->t = time;
	}
}

void	mmsg_hook(void *param)
{
	t_m	*m;
	m = param;
	double	time;
	
	time = mlx_get_time();
	if (time - m->men->t > m->men->speed)
	{
		if (m->men->msg->i < m->men->msg->num_of_f - 1)
			m->men->msg->i++;
		else
			m->men->msg->i = 0;
		mlx_image_to_window(m->map->mlx, m->men->msg->img[m->men->msg->i], MSG_W, MSG_H);
		m->men->t = time;
	}
}

void	register_hooks(t_m *m)
{
	mlx_loop_hook(m->map->mlx, &main_hooks, m);
	// mlx_loop_hook(m->map->mlx, &mmsg_hook, m);
	mlx_loop_hook(m->map->mlx, &menu_hook, m);
}
