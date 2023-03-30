#include "../../include/cub3d.h"
#include <stdio.h>

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
    int half_size = size / 2;
	x -= half_size;
	y -= half_size;
    double radians = dir * M_PI / 180.0;
    t_point p1 = {x + half_size * cos(radians), y + half_size * sin(radians)};
    t_point p2 = {x - half_size * cos(radians + M_PI / 6), y - half_size * sin(radians + M_PI / 6)};
    t_point p3 = {x - half_size * cos(radians - M_PI / 6), y - half_size * sin(radians - M_PI / 6)};

    int minX = fmin(p1.x, fmin(p2.x, p3.x));
    int minY = fmin(p1.y, fmin(p2.y, p3.y));
    int maxX = fmax(p1.x, fmax(p2.x, p3.x));
    int maxY = fmax(p1.y, fmax(p2.y, p3.y));

    t_point current;
    current.y = minY;
    while(current.y <= maxY) {
        current.x = minX;
        while(current.x <= maxX) {
			if (is_in_triangle(p1, p2, p3, current))
                draw_pixel(m, current.x, current.y, 0xFF0000FF);
            current.x++;
        }
        current.y++;
    }
}

static double	to_angle(t_m *m)
{
	double	radians;
	double	degrees;

	radians = atan2(m->t->diry, m->t->dirx);
    degrees = radians * 180.0 / M_PI;
    return (degrees);
}

static void	draw_player(t_m *m)
{
	int	mh;
	int	mw;
	int	rh;
	int	rw;

	mh = m->map->minmap_scale * m->p->size.x;
	mw = m->map->minmap_scale * m->p->size.y;
	rh = mh / m->p->size.x;
	rw = mw / m->p->size.y;
	draw_triangle(m, (m->t->posx * rw) + m->map->minmap_scale + 20,
			(m->t->posy * rh) + m->map->minmap_scale + 20, 10, to_angle(m));
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
