#include "../../include/cub3d.h"
#include <stdio.h>
#include <sys/fcntl.h>
#include <sys/syslimits.h>

static void	draw_square(t_m *m, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < m->map->minmap_scale)
	{
		j = 0;
		while (j < m->map->minmap_scale)
		{
			draw_pixel(m, x + i + 20, y + j + 20, color);
			j++;
		}
		i++;
	}
}

static bool	is_in_triangle(t_point p1, t_point p2, t_point p3, t_point p)
{
	double ab = (p2.y - p1.y) * (p.x - p1.x) - (p2.x - p1.x) * (p.y - p1.y);
	double bc = (p3.y - p2.y) * (p.x - p2.x) - (p3.x - p2.x) * (p.y - p2.y);
	double ca = (p1.y - p3.y) * (p.x - p3.x) - (p1.x - p3.x) * (p.y - p3.y);
	return ((ab >= 0 && bc >= 0 && ca >= 0) || (ab <= 0 && bc <= 0 && ca <= 0));
}

static void draw_triangle(t_m *m, int x, int y, int size, double dir)
{
    double angle = dir * M_PI / 180.0;
    double cos_a = cos(angle);
    double sin_a = sin(angle);
    int half_size = size / 2;
	x -= half_size;
	y -= half_size;

	t_point p1 = {x + (int)round(half_size * cos_a) * 1.75, y + (int)round(half_size * sin_a) * 1.75};
	t_point p2 = {x + (int)round(half_size * cos(angle + 2*M_PI/3)), y + (int)round(half_size * sin(angle + 2*M_PI/3))};
	t_point p3 = {x + (int)round(half_size * cos(angle + 4*M_PI/3)), y + (int)round(half_size * sin(angle + 4*M_PI/3))};

	t_point min = {fmin(fmin(p1.x, p2.x), p3.x), fmin(fmin(p1.y, p2.y), p3.y)};
	t_point max = {fmax(fmax(p1.x, p2.x), p3.x), fmax(fmax(p1.y, p2.y), p3.y)};
    int i = min.x;
    while (i <= max.x)
    {
        int j = min.y;
        while (j <= max.y)
        {
            if (is_in_triangle(p1, p2, p3, (t_point){i, j}))
				draw_pixel(m, i, j, 0xFF0000FF);
            j++;
        }
        i++;
    }
}

static double	to_angle(t_vec dir)
{
	double	radians;
	double	degrees;

	radians = atan2(dir.y, dir.x);
    degrees = radians * 180.0 / M_PI;
    return (degrees);
}

static void	draw_player(t_m *m)
{
	int	mh;
	int	mw;
	int	rh;
	int	rw;

	mh = m->map->minmap_scale * m->p->size.y;
	mw = m->map->minmap_scale * m->p->size.x;
	rh = mh / m->p->size.y;
	rw = mw / m->p->size.x;

	draw_triangle(m, (m->map->player->pos.x * rw) + m->map->minmap_scale + 20,
			(m->camera->pos.y * rh) + m->map->minmap_scale + 20, 10, to_angle(m->map->player->dir));
}

void	minimap(t_m	*m)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	m->map->minmap_scale = 200 / m->p->size.x;
	while (i < m->p->size.y)
	{
		j = 0;
		while (j < m->p->size.x)
		{
			if (m->p->map[i][j] == '1')
				draw_square(m, x, y, m->map->color);
			else if (m->p->map[i][j] == '0' || ft_strchr("WESN", m->p->map[i][j]))
				draw_square(m, x, y, m->map->colorf);
			j++;
			x += m->map->minmap_scale;
		}
		i++;
		x = 0;
		y += m->map->minmap_scale;
	}
	draw_player(m);
}
