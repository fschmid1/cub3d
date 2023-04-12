#include "../../include/cub3d.h"

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
	m->t->deltadistx = fabs(1 / m->t->raydirx);
	m->t->deltadisty = fabs(1 / m->t->raydiry);
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
	while(m->t->hit == 0)
	{
		if (m->t->sidedistx < m->t->sidedisty)
		{
			m->t->sidedistx += m->t->deltadistx;
			m->t->mapx += m->t->stepx;
			m->t->side = 0;
			m->t->wall = EA;
			if (m->t->raydirx < 0)
				m->t->wall = WE;
		}
		else
		{
			m->t->sidedisty += m->t->deltadisty;
			m->t->mapy += m->t->stepy;
			m->t->side = 1;
			m->t->wall = SO;
			if (m->t->raydiry < 0)
				m->t->wall = NO;
		}
		if (m->t->map[m->t->mapy][m->t->mapx] > 0)
			m->t->hit = 1;
	}
}

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
		if(m->t->side == 1)
			draw_pixel(m, m->x, i, ((m->map->color >> 1) & 8355711));
		else
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

int	calc_tex(t_m *m)
{
	int ret;
	double wallx;

	ret = 0;
	if (m->t->wall == EA || m->t->wall == WE)
		wallx = (m->t->posy + m->t->pwd * m->t->raydiry);
	if (m->t->wall == SO || m->t->wall == NO)
		wallx = (m->t->posx + m->t->pwd * m->t->raydirx);
	wallx -= floor(wallx);
	ret = (int)(wallx * (double)(m->tex[m->t->wall]->width));
	if (m->t->wall == WE || m->t->wall == SO)
		ret = m->tex[m->t->wall]->width - ret - 1;
	return (ret);
}

void	draw_textures(t_m *m)
{
	double	what;
	double	position;
	int	tex;
	int	tey;
	int width = m->tex[NO]->height;

	what = 1.00 * width / m->t->line_height;
	position = (m->t->draw_start - (m->window_h + m->t->line_height) /2) * what;
	tex = calc_tex(m);
	while(m->t->draw_start <= m->t->draw_end)
	{
		tey = (int)position + (width - 1);
		position += what;
		ft_memcpy(&m->map->img->pixels[(m->t->draw_start * m->window_w + m->x) * 4],
			&m->tex[m->t->wall]->pixels[(tey * width + tex) * 4], 4);
		m->t->draw_start++;
	}
}

void	draw_lines(t_m *m)
{
	m->t->line_height = (int)(m->window_h / m->t->pwd);
	m->t->draw_start = -m->t->line_height / 2 + m->window_h / 2;
	m->t->draw_end = m->t->line_height / 2 + m->window_h / 2;
	if (m->t->draw_start < 0)
		m->t->draw_start = 0;
	if (m->t->draw_end >= m->window_h)
		m->t->draw_end = m->window_h - 1;
	draw_ceiling(m);
	draw_textures(m);
	// draw_wall(m);
}

void	movspeed(t_m *m)
{
	m->t->old_time = m->t->time;
	m->t->time = mlx_get_time();
	m->t->frametime = (m->t->time - m->t->old_time) / 1000;
	// printf("TIME: %f, FRAME°TI°ME: %f\n", m->t->time, m->t->frametime * 1000000);
	// mlx_put_string(m->map->mlx, "FPS", 1800, 50);
	m->t->movspeed = m->t->frametime * 5000;
	m->t->rotspeed = m->t->frametime * 3000;
	// printf("FPS:%f\n", (1.0/(m->t->frametime * 1000)));
}

void	movement(t_m *m)
{
	if (mlx_is_key_down(m->map->mlx, MLX_KEY_W))
	{
		if (m->t->map[(int)m->t->posy][(int)(m->t->posx + m->t->dirx * m->t->movspeed)] == FALSE)
			m->t->posx += m->t->dirx * m->t->movspeed;
		if (m->t->map[(int)(m->t->posy + m->t->diry * m->t->movspeed)][(int)(m->t->posx)] == FALSE)
			m->t->posy += m->t->diry * m->t->movspeed;
		m->x = 0;
	}
	if (mlx_is_key_down(m->map->mlx, MLX_KEY_S))
	{
		if (m->t->map[(int)m->t->posy][(int)(m->t->posx - m->t->dirx * m->t->movspeed)] == FALSE)
			m->t->posx -= m->t->dirx * m->t->movspeed;
		if (m->t->map[(int)(m->t->posy - m->t->diry * m->t->movspeed)][(int)(m->t->posx)] == FALSE)
			m->t->posy -= m->t->diry * m->t->movspeed;
		m->x = 0;
	}
	if (mlx_is_key_down(m->map->mlx, MLX_KEY_A))
	{
		if (m->t->map[(int)m->t->posy][(int)(m->t->posx - m->t->planex * m->t->movspeed)] == FALSE)
			m->t->posx -= m->t->planex * m->t->movspeed;
		if (m->t->map[(int)(m->t->posy - m->t->planey * m->t->movspeed)][(int)(m->t->posx)] == FALSE)
			m->t->posy -= m->t->planey * m->t->movspeed;
		m->x = 0;
	}
	if (mlx_is_key_down(m->map->mlx, MLX_KEY_D))
	{
		if (m->t->map[(int)m->t->posy][(int)(m->t->posx + m->t->planex * m->t->movspeed)] == FALSE)
			m->t->posx += m->t->planex * m->t->movspeed;
		if (m->t->map[(int)(m->t->posy + m->t->planey * m->t->movspeed)][(int)(m->t->posx)] == FALSE)
			m->t->posy += m->t->planey * m->t->movspeed;
		m->x = 0;
	}
	if (mlx_is_mouse_down(m->map->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		m->firing = 1;
		m->x = 0;
	}
	else
		m->firing = 0;
}


void	value(t_m *m)
{
	printf("-----------------------------------------\n");
	printf("m->X = %i\n", m->x);
	printf("POSX:%f POSY%f\n", m->t->posx, m->t->posy);
	printf("DIRX:%f DIRY%f\n", m->t->dirx, m->t->diry);
	printf("SIDEDISTX:%f SIDEDISTY%f\n", m->t->sidedistx, m->t->sidedisty);
	printf("DELTADISTX:%f DELTADISTY%f\n", m->t->deltadistx, m->t->deltadisty);
	printf("RAYDIRX:%f RAYDIRY%f\n", m->t->raydirx, m->t->raydiry);
	printf("RAYDIRX:%f RAYDIRY%f\n", m->t->raydirx, m->t->raydiry);
}

void	crosshair(t_m *m)
{
	unsigned int i;
	unsigned int c;
	int pos;

	i = 0;
	c = 0;
	pos = m->window_h / 2 * m->window_w / 1.2 + 820;
	while (i++ < (m->cross->width * m->cross->height))
	{
		if (c == m->cross->width)
		{
			c = 0;
			pos += m->men->tex[0]->width - m->cross->width;
		}
		c++;
		if(m->cross->pixels[(i) * 4] != 0)
		{
			ft_memcpy(&m->map->img->pixels[(pos + i) * 4],
				&m->cross->pixels[(i) * 4], 4);
		}
	}
}
void	muzzle(t_m *m)
{
	unsigned int i;
	unsigned int c;
	int pos;

	i = 0;
	c = 0;
	pos = m->window_h / 2 * m->window_w / 1.21 + 115;
	while (i++ < (m->muzzle->width * m->muzzle->height))
	{
		if (c == m->muzzle->width)
		{
			c = 0;
			pos += m->men->tex[0]->width - m->muzzle->width;
		}
		c++;
		if(m->muzzle->pixels[(i) * 4] != 0)
		{
			ft_memcpy(&m->map->img->pixels[(pos + i) * 4],
				&m->muzzle->pixels[(i) * 4], 4);
		}
	}
}
void gun(t_m *m)
{

    unsigned int x, y;
    int pos;

    x = 0;
    y = 0;
    pos = m->window_h / 1.7 * m->window_w / 1.2 - 100;
    unsigned int copy_width = m->gun->width;
    unsigned int copy_height = m->gun->height;
    unsigned int max_x = copy_width;
    unsigned int max_y = copy_height;
	if (m->firing == 1)
		muzzle(m);
    while (y < max_y)
    {
        x = 0;
        while (x < max_x)
        {
            if((m->gun->pixels[(y * m->gun->width + x) * 4] != 0)
			&& (pos + y * m->men->tex[0]->width + x) < (unsigned int)(m->window_h * m->window_w))
            {
                ft_memcpy(&m->map->img->pixels[(pos + y * m->men->tex[0]->width + x) * 4],
                          &m->gun->pixels[(y * m->gun->width + x) * 4], 4);
            }
            x++;
        }
        y++;
    }
	if (m->firing == 1)
	{
		m->firing = 0;
		m->x = 0;
	}
}


void	fps_counter(t_m *m)
{
	char	*fps;
	char	*num;

	mlx_delete_image(m->map->mlx, m->map->fps);
	num = ft_itoa((int)((1.0/(m->t->frametime * 1000))));
	fps = ft_strjoin("FPS ", num);
	m->map->fps = mlx_put_string(m->map->mlx, fps, 1800, 50);
	free(num);
	free(fps);
}

void	game_loop(void *param)
{
	t_m	*m;
	m = param;

	movement(m);
	movspeed(m);
	if (m->x == 0)
	{
		ft_memset(m->map->img->pixels, 0,
		m->window_w * m->window_h * sizeof(int32_t));
	}
	while (m->x <= m->window_w)
	{
		set_values(m);
		delta_step(m);
		dda(m);
		perp_wd(m);
		draw_lines(m);
		m->x++;
	}
	gun(m);
	fps_counter(m);
	// crosshair(m);
	minimap(m);
}
