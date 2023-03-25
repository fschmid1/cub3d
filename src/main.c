/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:52:17 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/24 20:50:36 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_m	*m;

	m = setup_main();
	input_check(m->p, argc, argv);
	testing(m->p);
	setup_window(m);
	draw_menu(m);
	printf("done\n");
	register_hooks(m);
	mlx_loop(m->map->mlx);
	mlx_terminate(m->map->mlx);
	free_main(m);
	return (0);
}
