#include "../include/cub3d.h"

void	set_values(t_m *m)
{
	m->t->camerax = 2 * m->x / (double)m->window_w - 1; //pos = camera_x
	m->t->raydirx = m->t->dirx + m->t->planex * m->t->camerax;
	m->t->raydiry = m->t->diry + m->t->planey * m->t->camerax;
	m->t->mapx = (int)m->t->posx;
	m->t->mapy = (int)m->t->posy;
}

void	delta_step(t_m *m)
{
	m->t->deltadistx = /* m->t->raydirx == 0 ? INT_MAX :  */fabs(1 / m->t->raydirx); //DIFF
	m->t->deltadisty = /* m->t->raydiry == 0 ? INT_MAX :  */fabs(1 / m->t->raydiry);
	m->t->hit = 0;
	if (m->t->raydirx < 0)
	{
		m->t->stepx = -1;
		m->t->sidedistx = (m->t->posx - m->t->mapx) * m->t->deltadistx;
	}
	else
	{
		m->t->stepx = 1;
		m->t->sidedistx = (m->t->mapx + 1.0 - m->t->posx) * m->t->deltadistx;
	}
	if (m->t->raydiry < 0)
	{
		m->t->stepy = -1;
		m->t->sidedisty = (m->t->posy - m->t->mapy) * m->t->deltadisty;
	}
	else
	{
		m->t->stepy = 1;
		m->t->sidedisty = (m->t->mapy + 1.0 - m->t->posy) * m->t->deltadisty;
	}
}

void	dda(t_m *m)
{
		// printf("MAP SIDE DIST:X:%f: Y:%f:\n", m->t->sidedistx, m->t->sidedisty);
	while(m->t->hit == 0)
	{
		if (m->t->sidedistx < m->t->sidedisty)
		{
			m->t->sidedistx += m->t->deltadistx;
			m->t->mapx += m->t->stepx;
			m->t->side = 0;
		}
		else
		{
			m->t->sidedisty += m->t->deltadisty;
			m->t->mapy += m->t->stepy;
			m->t->side = 1;
		}
		if (m->t->map[m->t->mapy][m->t->mapx] > 0)
			m->t->hit = 1;
	}
}

// void	perp_wd(t_m *m)
// {
// 	if (m->camera->side == 0)
// 		m->t->pwd = (m->t->mapx - m->t->posx + (1 - m->t->stepx) / 2) / m->t->dirx;
// 	else
// 		m->t->pwd = (m->t->mapy - m->t->posy + (1 - m->t->stepy) / 2) / m->t->diry;
// }

void	perp_wd(t_m *m)
{
	if (m->t->side == 0)
		m->t->pwd = (m->t->sidedistx - m->t->deltadistx);
	else
		m->t->pwd = (m->t->sidedisty - m->t->deltadisty);
}

void	draw_wall(t_m *m)
{
	int i;

	i = m->t->draw_start;
	while (i < m->t->draw_end)
	{
		draw_pixel(m, m->x, i, m->map->color);
		i++;
	}
}
void	draw_ceiling(t_m *m)
{
	int i;

	i = 0;
	while (i < m->window_h)
	{
		if (i < m->t->draw_start)
			draw_pixel(m, m->x, i, m->map->colorc);
		else if (i > m->t->draw_end)
			draw_pixel(m, m->x, i, m->map->colorf);
		i++;
	}
}

void	draw_lines(t_m *m)
{
	m->t->line_height = 0;
	m->t->draw_start = 0;
	m->t->draw_end = 0;
	m->t->line_height = (int)(m->window_h / m->t->pwd);
	m->t->draw_start = -m->t->line_height / 2 + m->window_h / 2;
	m->t->draw_end = m->t->line_height / 2 + m->window_h / 2;
	if (m->t->draw_start < 0)
		m->t->draw_start = 0;
	if (m->t->draw_end >= m->window_h)
		m->t->draw_end = m->window_h - 1;
	// if (m->t->side == 1)
	// 	m->map->color = 0x333333FF;
	// else
	// 	m->map->color = 0xFFFFFFFF;
	// printf("LINE HEIGHT: %i P_WD.%f \nDRAW START %i DRAW END %i\n", m->t->line_height, m->t->pwd, m->t->draw_start, m->t->draw_end);
	// printf("BROKE AT CEILING\n");
	draw_ceiling(m);
	draw_wall(m);
	// printf("BROKE AT WALL\n");
}

void	movspeed(t_m *m)
{
	m->t->old_time = m->t->time;
	m->t->time = mlx_get_time();
	m->t->frametime = (m->t->time - m->t->old_time) / 1000;
	// printf("FPS:%f\n", (1.0/m->frametime));
	m->t->movspeed = m->t->frametime * 5000;
	m->t->rotspeed = m->t->frametime * 3000;
}

void	movement(t_m *m)
{
	if (mlx_is_key_down(m->map->mlx, MLX_KEY_UP))
	{
		if (m->t->map[(int)(m->t->posx + m->t->dirx * m->t->movspeed)][(int)m->t->posy] == FALSE)
			m->t->posx += m->t->dirx * m->t->movspeed;
		if (m->t->map[(int)(m->t->posx)][(int)(m->t->posy + m->t->diry * m->t->movspeed)] == FALSE)
			m->t->posy += m->t->diry * m->t->movspeed;
		m->x = 0;
	}
	if (mlx_is_key_down(m->map->mlx, MLX_KEY_DOWN))
	{
		if (m->t->map[(int)(m->t->posx - m->t->dirx * m->t->movspeed)][(int)m->t->posy] == FALSE)
			m->t->posx -= m->t->dirx * m->t->movspeed;
		if (m->t->map[(int)(m->t->posx)][(int)(m->t->posy - m->t->diry * m->t->movspeed)] == FALSE)
			m->t->posy -= m->t->diry * m->t->movspeed;
		m->x = 0;
	}
	if (mlx_is_key_down(m->map->mlx, MLX_KEY_LEFT))
	{
		m->t->olddirx = m->t->dirx;
		m->t->dirx = m->t->dirx * cos(-m->t->rotspeed) - m->t->diry * sin(-m->t->rotspeed);
		m->t->diry = m->t->olddirx * sin(-m->t->rotspeed) + m->t->diry * cos(-m->t->rotspeed);
		m->t->oldplanex = m->t->planex;
		m->t->planex = m->t->planex * cos(-m->t->rotspeed) - m->t->planey * sin(-m->t->rotspeed);
		m->t->planey = m->t->oldplanex * sin(-m->t->rotspeed) + m->t->planey * cos(-m->t->rotspeed);
		m->x = 0;
	}
	if (mlx_is_key_down(m->map->mlx, MLX_KEY_RIGHT))
	{
		m->t->olddirx = m->t->dirx;
		m->t->dirx = m->t->dirx * cos(m->t->rotspeed) - m->t->diry * sin(m->t->rotspeed);
		m->t->diry = m->t->olddirx * sin(m->t->rotspeed) + m->t->diry * cos(m->t->rotspeed);
		m->t->oldplanex = m->t->planex;
		m->t->planex = m->t->planex * cos(m->t->rotspeed) - m->t->planey * sin(m->t->rotspeed);
		m->t->planey = m->t->oldplanex * sin(m->t->rotspeed) + m->t->planey * cos(m->t->rotspeed);
		m->x = 0;
	}
}


void	value(t_m *m)
{
	printf("-----------------------------------------\n");
	printf("POSX:%f POSY%f\n", m->t->posx, m->t->posy);
	printf("DIRX:%f DIRY%f\n", m->t->dirx, m->t->diry);
	printf("SIDEDISTX:%f SIDEDISTY%f\n", m->t->sidedistx, m->t->sidedisty);
	printf("DELTADISTX:%f DELTADISTY%f\n", m->t->deltadistx, m->t->deltadisty);
	printf("RAYDIRX:%f RAYDIRY%f\n", m->t->raydirx, m->t->raydiry);
	printf("RAYDIRX:%f RAYDIRY%f\n", m->t->raydirx, m->t->raydiry);
}

void	game_loop(void *param)
{
	t_m	*m;
	m = param;

	// printf("BROKE AT MOVSPEED\n");
	movspeed(m);
	// printf("BROKE AT MOVEMENT\n");
	movement(m);
	if (m->x == 0)
	{
		ft_memset(m->map->img->pixels, 0,
		m->window_w * m->window_h * sizeof(int32_t));
	// 	printf("POSX:%f POSY%f\n", m->t->posx, m->t->posy);
	// printf("DIRX:%f DIRY%f\n", m->t->dirx, m->t->diry);
		// test_values(m);	
	}
	while (m->x < m->window_w)
	{
		// value(m);
		// printf("BROKE AT VALUES\n");
		set_values(m);
		// value(m);
		// printf("BROKE AT DELTASTEP\n");
		delta_step(m);
		// value(m);
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
}