/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:52:17 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/24 20:03:13 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdio.h>

void	draw_menu(t_m *m)
{
	m->men->m1 = mlx_load_png("src/1.png");
	m->men->m2 = mlx_load_png("src/2.png");
	m->men->m1i = mlx_texture_to_image(m->map->mlx, m->men->m1);
	m->men->m2i = mlx_texture_to_image(m->map->mlx, m->men->m2);
	mlx_image_to_window(m->map->mlx, m->men->m1i, 0, 0);
}

int	main(int argc, char **argv)
{
	t_m	*m;

	m = setup_main();
	input_check(m->p, argc, argv);
	testing(m->p);
	setup_window(m);
	draw_menu(m);
	register_hooks(m);
	mlx_loop(m->map->mlx);
	mlx_terminate(m->map->mlx);
	free_main(m);
	return (0);
}
