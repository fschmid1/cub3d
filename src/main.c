/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:52:17 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/26 16:01:50 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdio.h>


void	set_position(t_m *m)
{
	m->map->map = dblcpy_to_int(m->p->intmap, m->p->size.x, m->p->size.y);
	m->camera->pos = m->p->pos_p; // sets player start position
	// m->camera->pos = (t_vec){m->p->pos_p.x, m->p->pos_p.y, 0}; // sets player start position
	// m->camera->map = m->camera->pos; // initial camera position
	// m->camera->dir = (t_vec){-1, 0, 0}; // initial direction vector
	// 2d raycaster of camera plane
	m->time = 0; // time of current frame 
	m->old_time = 0; // time  of previous frame
	m->map->color = 0xFFFFFF;
	// m->camera->pos.x = 2;
	// m->map->step = (t_vec){0, 0, 0};
	// m->camera->ray_dir.x = m->camera->ray_dir.x + m->camera->plane.x * m->camera->pos.x;
	// m->camera->ray_dir.y = m->camera->ray_dir.y + m->camera->plane.y * m->camera->pos.x;
	// m->camera->delta_dist.x = m->camera->ray_dir.x == 0 ? INT_MAX : fabs(1 / m->camera->ray_dir.x);
	// m->camera->delta_dist.y = m->camera->ray_dir.y == 0 ? INT_MAX : fabs(1 / m->camera->ray_dir.y);
}

int	main(int argc, char **argv)
{
	t_m	*m;

	m = setup_main();
	input_check(m->p, argc, argv);
	printf("-------------------INPUT CHECK DONE-------------\n");
	testing(m->p);
	printf("--------------------TESTING DONE----------------\n");
	setup_window(m);
	printf("--------------------WINDOW DONE----------------\n");
	// draw_msg(m);
	// draw_menu(m);
	m->map->map = dblcpy_to_int(m->p->intmap, m->p->size.x, m->p->size.y);
	m->map->player = setup_player(m);
	printf("--------------------PLAYER SETUP ----------------\n");
	m->camera = setup_camera(m);
	printf("--------------------CAMERA SETUP ----------------\n");
	set_position(m);
	printf("--------------------POSITION SETUP----------------\n");
	game_loop(m);
	printf("--------------------GAME LOOP RUNNING ONCE----------------\n");
	register_hooks(m);
	mlx_loop(m->map->mlx);
	mlx_terminate(m->map->mlx);
	free_main(m);
	return (0);
}
