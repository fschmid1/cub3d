/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 19:37:45 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/27 15:34:32 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/cub3d.h"

void	set_values(t_m *m)
{
	m->camera->pos.x = 2 * m->x / (double)m->window_w - 1; //pos = camera_x
	m->camera->ray_dir.x = m->camera->ray_dir.x + m->camera->plane.x * m->camera->pos.x;
	m->camera->ray_dir.y = m->camera->ray_dir.y + m->camera->plane.y * m->camera->pos.y;
	m->camera->map_x = (int)m->camera->ray_pos.x;
	m->camera->map_y = (int)m->camera->ray_pos.y;
}

void	delta_step(t_m *m)
{
	m->camera->delta_dist.x = /* m->camera->ray_dir.x == 0 ? INT_MAX :  */fabs(1 / m->camera->ray_dir.x); //DIFF
	m->camera->delta_dist.y = /* m->camera->ray_dir.y == 0 ? INT_MAX :  */fabs(1 / m->camera->ray_dir.y);
	m->camera->hit = 0;
	if (m->camera->ray_dir.x < 0)
	{
		m->camera->step.x = -1;
		m->camera->side_dist.x = (m->camera->ray_pos.x - m->camera->map_x) * m->camera->delta_dist.y;
	}
	else
	{
		m->camera->step.x = 1;
		m->camera->side_dist.x = (m->camera->map_x + 1.0 - m->camera->ray_pos.x) * m->camera->delta_dist.y;
	}
	if (m->camera->ray_dir.y < 0)
	{
		m->camera->step.y = -1;
		m->camera->side_dist.y = (m->camera->ray_pos.y - m->camera->map_y) * m->camera->delta_dist.x;
	}
	else
	{
		m->camera->step.y = 1;
		m->camera->side_dist.y = (m->camera->map_y + 1.0 - m->camera->ray_pos.y) * m->camera->delta_dist.x;
	}
}

void	dda(t_m *m)
{
	while(m->camera->hit == 0)
	{
		// printf("MAP SIDE DIST:X:%f: Y:%f: Z:%f\n", m->camera->side_dist.x, m->camera->side_dist.y, m->camera->side_dist.z);
		// printf("MAP DELT DIST:X:%f: Y:%f: Z:%f\n", m->camera->delta_dist.x, m->camera->delta_dist.y, m->camera->delta_dist.z);
		if (m->camera->side_dist.x < m->camera->side_dist.y)
		{
			m->camera->side_dist.x += m->camera->delta_dist.y;
			m->camera->map_x += m->camera->step.x;
			m->camera->side = 0;
		}
		else
		{
			m->camera->side_dist.y += m->camera->delta_dist.x;
			m->camera->map_y += m->camera->step.y;
			m->camera->side = 1;
		}
		if (m->map->map[m->camera->map_x][m->camera->map_y] > 0)
			m->camera->hit = 1;
	}
}

void	perp_wd(t_m *m)
{
	if (m->camera->side == 0)
		m->camera->perp_wd = (m->camera->map_x - m->camera->pos.x + (1 - m->camera->step.x) / 2) / m->camera->ray_dir.x;
	else
		m->camera->perp_wd = (m->camera->map_y - m->camera->pos.y + (1 - m->camera->step.y) / 2) / m->camera->ray_dir.y;
}

void	draw_wall(t_m *m, int x, int start, int end)
{
	while (start < end)
	{
		mlx_put_pixel(m->map->img, x, start, m->map->color);
		start++;
	}
}
void	draw_ceiling(t_m *m, int x, int start, int end)
{
	int i;

	i = 0;
	while (i < m->window_h)
	{
		if (i < start)
			mlx_put_pixel(m->map->img, x, i, m->map->colorc);
		else if (i < end)
			mlx_put_pixel(m->map->img, x, i, m->map->colorf);
		i++;
	}
}

void	draw_lines(t_m *m)
{
	int	line_height;
	int draw_start;
	int draw_end;

	line_height = 0;
	draw_start = 0;
	draw_end = 0;
	// printf("LINE HEIGHT: %i P_WD.%f \nDRAW START %i DRAW END %i\n", line_height, m->camera->perp_wd, draw_start, draw_end);
	line_height = (int)(m->window_h / m->camera->perp_wd);
	draw_start = -line_height / 2 + m->window_h / 2;
	draw_end = line_height / 2 + m->window_h / 2;
	if (draw_start < 0)
		draw_start = 0 + 1;
	if (draw_end >= m->window_h)
		draw_end = m->window_h - 1;
	// if (m->camera->side == 1)
	// 	m->map->color = 0x333333FF;
	// draw_wall(m, m->x, draw_start, draw_end);
	draw_ceiling(m, m->x, draw_start, draw_end);
}

void	movspeed(t_m *m)
{
	m->old_time = m->time;
	m->time = mlx_get_time();
	m->frametime = (m->time - m->old_time) / 1000;
	// printf("FPS:%f\n", (1.0/m->frametime));
	m->camera->mspeed = m->frametime * 0.5;
	m->camera->rspeed = m->frametime * 0.3;
}

void	movement(t_m *m)
{
	if (mlx_is_key_down(m->map->mlx, MLX_KEY_UP))
	{
		if (m->map->map[(int)(m->map->player->pos.x + m->map->player->dir.x * m->camera->mspeed)][(int)m->map->player->pos.y] == FALSE)
			m->map->player->pos.x += m->map->player->dir.x * m->camera->mspeed;
		if (m->map->map[(int)m->map->player->pos.x][(int)(m->map->player->pos.y + m->camera->ray_dir.y * m->camera->mspeed)] == FALSE)
			m->map->player->pos.y += m->map->player->pos.y - m->map->player->dir.y * m->camera->mspeed;
		m->x = 0;
	}
	if (mlx_is_key_down(m->map->mlx, MLX_KEY_DOWN))
	{
		if (m->map->map[(int)(m->map->player->pos.x - m->map->player->dir.x * m->camera->mspeed)][(int)m->map->player->pos.y] == FALSE)
			m->map->player->pos.x -= m->map->player->dir.x * m->camera->mspeed;
		if (m->map->map[(int)m->map->player->pos.x][(int)(m->map->player->pos.y - m->map->player->dir.y * m->camera->mspeed)] == FALSE)
			m->map->player->pos.y -= m->map->player->pos.y - m->map->player->dir.y * m->camera->mspeed;
		m->x = 0;
	}
	if (mlx_is_key_down(m->map->mlx, MLX_KEY_LEFT))
	{
		m->camera->old_ray_dir.x = m->camera->ray_dir.x;
		m->camera->ray_dir.x = m->camera->ray_dir.x * cos(-m->camera->rspeed) - m->camera->ray_dir.y * sin(-m->camera->rspeed);
		m->camera->ray_dir.y = m->camera->old_ray_dir.x * sin(-m->camera->rspeed) + m->camera->ray_dir.y * cos(-m->camera->rspeed);
		m->camera->old_plane.x = m->camera->plane.x;
		m->camera->plane.x = m->camera->plane.x * cos(m->camera->rspeed) - m->camera->plane.y * sin(m->camera->rspeed);
		m->camera->plane.y = m->camera->old_plane.x * sin(m->camera->rspeed) + m->camera->plane.y * cos(m->camera->rspeed);
		m->x = 0;
	}
	if (mlx_is_key_down(m->map->mlx, MLX_KEY_RIGHT))
	{
		m->camera->old_ray_dir.x = m->camera->ray_dir.x;
		m->camera->ray_dir.x = m->camera->ray_dir.x * cos(m->camera->rspeed) - m->camera->ray_dir.y * sin(m->camera->rspeed);
		m->camera->ray_dir.y = m->camera->old_ray_dir.x * sin(m->camera->rspeed) + m->camera->ray_dir.y * cos(m->camera->rspeed);
		m->camera->old_plane.x = m->camera->plane.x;
		m->camera->plane.x = m->camera->plane.x * cos(m->camera->rspeed) - m->camera->plane.y * sin(m->camera->rspeed);
		m->camera->plane.y = m->camera->old_plane.x * sin(m->camera->rspeed) + m->camera->plane.y * cos(m->camera->rspeed);
		m->x = 0;
	}
}

void	game_loop(void *param)
{
	t_m	*m;
	m = param;

	movspeed(m);
	movement(m);
	// if (m->x == 0)
	// {
	// 	test_values(m);	
	// 	if (m->map->img)
	// 		mlx_delete_image(m->map->mlx, m->map->img);
	// 	m->map->img = mlx_new_image(m->map->mlx, m->window_w, m->window_h);
	// }
	while (m->x < m->window_w)
	{
		// printf("BROKE AT VALUES\n");
		set_values(m);
		// test_values(m);
		// printf("BROKE AT DELTASTEP\n");
		delta_step(m);
		// test_values(m);
		// printf("BROKE AT DDA\n");
		dda(m);
		// test_values(m);
		// printf("BROKE AT PER_WD\n");
		perp_wd(m);
		// test_values(m);
		// printf("BROKE AT DRAW LINES\n");
		draw_lines(m);
		m->x++;
	}
	minimap(m);
	// mlx_image_to_window(m->map->mlx, m->map->img, 0, 0);
}
