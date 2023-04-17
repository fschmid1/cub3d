/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:52:17 by pgorner           #+#    #+#             */
/*   Updated: 2023/04/17 11:43:04 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdio.h>


void	set_position(t_m *m)
{
	m->t = malloc(sizeof(t_t));
	m->t->map = dblcpy_to_int(m->p->intmap, m->p->size.y, m->p->size.x);
	m->t->posx = m->map->player->pos.x;
	m->t->posy = m->map->player->pos.y;
	m->t->dirx = m->map->player->dir.x;
	m->t->diry = m->map->player->dir.y;
	m->t->planex = 0.66;
	m->t->planey = 0.00;
	m->t->time = 0;
	m->t->old_time = 0;
	m->t->hit = 0;
	m->t->stepx = 0;
	m->t->stepy = 0;
	m->t->sidedistx = 0;
	m->t->sidedisty = 0;
	m->t->line_height = 0;
	m->t->draw_start = 0;
	m->t->draw_end = 0;
	m->t->mouse = (t_vec) {m->window_w / 2, m->window_h / 2, 0};
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
	load_wall(m);
	alloc_tex_im(m);
	load_textures(m, PATH);
	printf("--------------------WALLS DONE----------------\n");
	mlx_set_mouse_pos(m->map->mlx, m->window_w / 2, m->window_h / 2);
	draw_msg(m);
	m->map->map = dblcpy_to_int(m->p->intmap, m->p->size.y, m->p->size.x);
	m->map->player = setup_player(m);
	printf("--------------------PLAYER SETUP ----------------\n");
	m->camera = setup_camera(m);
	printf("--------------------T SETUP ----------------\n");
	set_position(m);
	register_hooks(m);
	mlx_loop(m->map->mlx);
	free_main(m);
	mlx_terminate(m->map->mlx);
	// system("leaks cub3D");
	return (0);
}
