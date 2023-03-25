/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 19:37:45 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/25 22:44:55 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/cub3d.h"

int	**dblcpy_to_int(int **src, int x, int y)
{
	int **dest;
	int	i;
	int	j;

	i = y;
	i = 0;
	j = 0;
	dest = malloc(sizeof(int *) * x);
	while (i < x)
	{
			dest[i] = src[i];
		i++;
	}
	return(dest);
}

void	set_position(t_m *m)
{
	m->map->map = dblcpy_to_int(m->p->intmap, m->p->size.x, m->p->size.y);
	m->camera->pos = (t_vec){m->p->pos_p.x, m->p->pos_p.y, 0}; // sets player start position
	m->camera->map = m->camera->pos; // initial direction vector
	m->camera->dir = (t_vec){-1, 0, 0}; // initial direction vector
	m->camera->plane = (t_vec){0, 0.66, 0}; // 2d raycaster of camera plane
	m->time = 0; // time of current frame 
	m->old_time = 0; // time  of previous frame
	m->map->color = 0xFFFFFF;
}

void	ray_posdir(t_m *m, int x)
{
	m->camera->pos.x = 2 * x / m->window_w - 1;
	m->camera->ray.x = m->camera->dir.x + m->camera->plane.x * m->camera->pos.x;
	m->camera->ray.y = m->camera->dir.y + m->camera->plane.y * m->camera->pos.x;
	m->map->delta_dist.x = m->camera->ray.x == 0 ? INT_MAX : fabs(1 / m->camera->ray.x);
	m->map->delta_dist.y = m->camera->ray.y == 0 ? INT_MAX : fabs(1 / m->camera->ray.y);
}

void	delta_step(t_m *m)
{
	m->map->hit = 0;
	if (m->camera->ray.x < 0)
	{
		m->map->step.x *= -1;
		m->map->side_dist.x = (m->camera->pos.x - m->camera->map.x) * m->map->delta_dist.x;
	}
	else
		m->map->side_dist.x = (m->camera->map.x + 1.0 - m->camera->pos.x) * m->map->delta_dist.x;
	if (m->camera->ray.y < 0)
	{
		m->map->step.y *= -1;
		m->map->side_dist.y = (m->camera->pos.y - m->camera->map.y) * m->map->delta_dist.y;
	}
	else
		m->map->side_dist.y = (m->camera->map.y + 1.0 - m->camera->pos.y) * m->map->delta_dist.y;
}

void	dda(t_m *m)
{
	while(m->map->hit == 0)
	{
		// printf("MAP SIDE DIST:X:%f: Y:%f: Z:%f\n", m->map->side_dist.x, m->map->side_dist.y, m->map->side_dist.z);
		// printf("MAP DELT DIST:X:%f: Y:%f: Z:%f\n", m->map->delta_dist.x, m->map->delta_dist.y, m->map->delta_dist.z);
		if (m->map->side_dist.x < m->map->side_dist.y)
		{
			m->map->side_dist.x += m->map->delta_dist.x;
			m->camera->map.x += m->map->step.x;
			m->map->side_hit = 0;
		}
		else
		{
			m->map->side_dist.y += m->map->delta_dist.y;
			m->camera->map.y += m->map->step.y;
			m->map->side_hit = 1;
		}
		if (m->map->map[(int)(m->camera->map.x)][(int)(m->camera->map.x)] > 0)
			m->map->hit = 1;
	}
}

void	perp_wd(t_m *m)
{
	if (m->map->side_hit == 0)
		m->map->perp_wd = (m->map->side_dist.x - m->map->delta_dist.x);
	else
		m->map->perp_wd = (m->map->side_dist.y - m->map->delta_dist.y);
}

void	draw_line(t_m *m, int x, int start, int end)
{
	printf("DRAW START %i DRAW END %i\n", start, end);
	while (start >= end)
	{
		mlx_put_pixel(m->map->img, x, start, m->map->color);
		start--;
	}
}

void	draw_lines(t_m *m, int x)
{
	int	line_height;
	int draw_start;
	int draw_end;
	
	
	line_height = (int)(m->window_h / m->map->perp_wd);
	draw_start = -line_height / 2 + m->window_h / 2;
	draw_end = line_height / 2 + m->window_h / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= m->window_h)
		draw_end = m->window_h - 1;
	// if (m->map->side_hit = 1)
	// 	color = color / 2;
	draw_line(m, x, draw_start, draw_end);
}

void	test_values(t_m *m)
{
	// dprinti(m->map->map, m->p->size.x, m->p->size.y);
	printf("----------------PARSE-------------------\n");
	printf("MAP PLAYER POS :X:%f: Y:%f: Z:%f\n", m->p->pos_p.x, m->p->pos_p.y, m->p->pos_p.z);
	printf("MAP PLAYER POS :X:%i: Y:%i: Z:%i\n", (int)m->p->pos_p.x, (int)m->p->pos_p.y, (int)m->p->pos_p.z);
	printf("----------------PLAYER-------------------\n");
	printf("MAP PLAYER POS :X:%f: Y:%f: Z:%f\n", m->map->player->pos.x, m->map->player->pos.y, m->map->player->pos.z);
	printf("MAP PLAYER DIR :X:%f: Y:%f: Z:%f\n", m->map->player->dir.x, m->map->player->dir.y, m->map->player->dir.z);
	printf("----------------NEW LINE-------------------\n");
	printf("MAP SIDE DIST:X:%f: Y:%f: Z:%f\n", m->map->side_dist.x, m->map->side_dist.y, m->map->side_dist.z);
	printf("MAP DELT DIST:X:%f: Y:%f: Z:%f\n", m->map->delta_dist.x, m->map->delta_dist.y, m->map->delta_dist.z);
	printf("MAP STEP:     X:%f: Y:%f: Z:%f\n", m->map->step.x, m->map->step.y, m->map->step.z);
	printf("MAP HIT:     %i\n", m->map->hit);
	printf("MAP SIDEHIT: %i\n", m->map->side_hit);
	printf("MAP PERP_WD: %f\n", m->map->perp_wd);
	printf("-------------------------------------------\n");
	printf("CAM DIR:  X:%f: Y:%f: Z:%f\n", m->camera->dir.x, m->camera->dir.y, m->camera->dir.z);
	printf("CAM RAY:  X:%f: Y:%f: Z:%f\n", m->camera->ray.x, m->camera->ray.y, m->camera->ray.z);
	printf("CAM PLANE:X:%f: Y:%f: Z:%f\n", m->camera->plane.x, m->camera->plane.y, m->camera->plane.z);
	printf("CAM POS:  X:%f: Y:%f: Z:%f\n", m->camera->pos.x, m->camera->pos.y, m->camera->pos.z);
	printf("CAM MAP:  X:%f: Y:%f: Z:%f\n", m->camera->map.x, m->camera->map.y, m->camera->map.z);
	printf("-------------------------------------------\n");
}

void	game_loop(t_m *m)
{
	int	x;

	x = 0;
	while (x < m->window_w)
	{
		// test_values(m);
		printf("BROKE AT POSDIR\n");
		ray_posdir(m, x);
		printf("BROKE AT DELTASTEP\n");
		delta_step(m);
		printf("BROKE AT DDA\n");
		dda(m);
		printf("BROKE AT PER_WD\n");
		perp_wd(m);
		draw_lines(m, x);
		x++;
	}
}
// void	game_loop(void *param)
// {
// 	t_m	*m;
// 	m = param;
// 	int	x;

// 	x = 0;
// 	if (x == 0)
// 	{
// 		testing(m->p);
// 		test_values(m);
// 	}
// 	while (x < 10)
// 	{
// 		ray_posdir(m, x);
// 		delta_step(m);
// 		dda(m);
// 		perp_wd(m);
// 		draw_lines(m, x);
// 		x++;
// 	}
// }