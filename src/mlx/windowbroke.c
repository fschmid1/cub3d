/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:53:00 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/24 19:38:33 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	setup_window(t_m *m)
{
	printf("w%i, h%i\n", m->window_w, m->window_h);
	m->mlx = mlx_init(m->window_w, m->window_h, "cub3d", true);
	if (!m->mlx)
		return (puts(mlx_strerror(mlx_errno)), EXIT_FAILURE);
	m->map->img = mlx_new_image(m->mlx, m->window_w, m->window_h);
	printf("map:%p\n", m->map->img);
	if (!m->map->img)
		return (mlx_close_window(m->map->mlx),
			puts(mlx_strerror(mlx_errno)), EXIT_FAILURE);
			mlx_image_to_window(m->mlx, m->map->img, 0, 0);
	// if (mlx_image_to_window(m->mlx, m->map->img, 0, 0) == -1)
		// return (mlx_close_window(m->map->mlx),
		// 	puts(mlx_strerror(mlx_errno)), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	main_hooks(void *param)
{
	t_m	*m;

	m = param;
	if (mlx_is_key_down(m->map->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(m->map->mlx);
}

void	menu_hook(void *param)
{
	t_m	*m;

	m = param;
	if (m->men == 0)
	{
		mlx_image_to_window(m->map->mlx, m->men->m2i, 0, 0);
		m->men++;
		sleep(1);
	}
	else if (m->men != 0)
	{
		mlx_image_to_window(m->map->mlx, m->men->m1i, 0, 0);
		m->men = 0;
		sleep(1);
	}
}

void	register_hooks(t_m *m)
{
	mlx_loop_hook(m->map->mlx, &main_hooks, m);
	mlx_loop_hook(m->map->mlx, &menu_hook, m);
}
