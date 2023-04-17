/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:06:08 by pgorner           #+#    #+#             */
/*   Updated: 2023/04/17 17:06:26 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_menu	*setup_menu(void)
{
	t_menu	*menu;

	menu = malloc(sizeof(t_menu));
	if (!menu)
		return (NULL);
	menu->t = 0;
	menu->i = 0;
	menu->speed = SPEED;
	menu->tex = NULL;
	menu->msg = NULL;
	return (menu);
}

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

void	set_position(t_m *m)
{
	m->t = malloc(sizeof(t_t));
	m->t->map = dblcpy_to_int(m->p->intmap, m->p->size.y, m->p->size.x);
	m->t->posx = m->p->pos_p.x;
	m->t->posy = m->p->pos_p.y;
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
	set_dir(m);
	m->t->mouse = (t_vec){m->window_w / 2, m->window_h / 2, 0};
}
