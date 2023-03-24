/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:53:00 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/24 15:53:36 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	setup_window(t_m *m)
{
	m->mlx = mlx_init(m->window_w, m->window_h, "cub3d", true);
	if (!m->mlx)
		return (puts(mlx_strerror(mlx_errno)), EXIT_FAILURE);
	m->img = mlx_new_image(m->mlx, m->window_w, m->window_h);
	if (!m->img)
		return (mlx_close_window(m->mlx),
			puts(mlx_strerror(mlx_errno)), EXIT_FAILURE);
	if (mlx_image_to_window(m->mlx, m->img, 0, 0) == -1)
		return (mlx_close_window(m->mlx),
			puts(mlx_strerror(mlx_errno)), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	main_hooks(void *param)
{
	t_m	*m;

	m = param;
	if (mlx_is_key_down(m->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(m->mlx);
}

void	register_hooks(t_m *m)
{
	mlx_loop_hook(m->mlx, &main_hooks, m);
}
