/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:54:02 by pgorner           #+#    #+#             */
/*   Updated: 2023/04/20 13:24:08 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	map_to_int(t_p *m)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	m->intmap = malloc(sizeof(int *) * m->size.y + 1);
	while (++i < m->size.y)
	{
		j = 0;
		m->intmap[i] = ft_calloc(sizeof(int), m->size.x + 1);
		while (m->map[i][j])
		{
			if (ispos_p(m->map[i][j]) == TRUE || m->map[i][j] == '0')
				m->intmap[i][j] = WALKABLE;
			else if (m->map[i][j] == '1')
				m->intmap[i][j] = WALL;
			else if (m->map[i][j] == 'd')
				m->intmap[i][j] = DOOR_OPEN;
			else if (m->map[i][j] == 'D')
				m->intmap[i][j] = DOOR_CLOSED;
			j++;
		}
	}
}

void	resize_map(t_p *m)
{
	int		x;
	int		y;
	char	**new;

	y = 0;
	new = ft_calloc(sizeof(char *), m->size.y + 1);
	while (y < m->size.y)
		new[y++] = ft_calloc(sizeof(char), m->size.x + 1);
	y = -1;
	while (++y < m->size.y)
	{
		x = -1;
		while (++x < m->size.x)
		{
			if ((!ft_strchr("01dD", m->map[y][x]) && ispos_p(m->map[y][x]) == 0)
				|| x >= (int)ft_strlen(m->map[y]))
				new[y][x] = '1';
			else
				new[y][x] = m->map[y][x];
		}
		new[y][x] = '\0';
	}
	free_string_array(m->map);
	m->map = doublcpy(new, m->size.y);
	free_string_array(new);
}

void	max_val(t_p *m)
{
	size_t	w;
	size_t	h;

	w = 0;
	h = 0;
	while (m->map[h])
	{
		if (ft_strlen(m->map[h]) > w)
			w = ft_strlen(m->map[h]);
		h++;
	}
	m->size = (t_vec){w, h, 0};
}

void	fill(t_p *m, t_point cur, char to_fill)
{
	if (!ft_strchr("01FdD", m->fmap[cur.y][cur.x])
		|| (m->fmap[cur.y][0] == '0')
		|| ((m->fmap[cur.y][cur.x] == '0')
			&& cur.y == 0)
		|| ((m->fmap[cur.y][cur.x] == '0')
			&& (!m->fmap[cur.y][cur.x + 1])))
		m->status = FALSE;
	else if (cur.x < 0 || cur.x >= (int)ft_strlen(m->fmap[cur.y])
		|| cur.y < 0 || cur.y >= m->size.y
		|| m->fmap[cur.y][cur.x] != to_fill)
		return ;
	m->fmap[cur.y][cur.x] = 'F';
	fill(m, (t_point){cur.x - 1, cur.y}, to_fill);
	fill(m, (t_point){cur.x + 1, cur.y}, to_fill);
	fill(m, (t_point){cur.x, cur.y - 1}, to_fill);
	fill(m, (t_point){cur.x, cur.y + 1}, to_fill);
}

void	check_map(t_p *m)
{
	int		i;
	t_point	size;

	i = 0;
	size = (t_point){m->size.x, m->size.y};
	m->fmap = doublcpy(m->map, m->size.y);
	m->fmap[(int)m->pos_p.y][(int)m->pos_p.x] = '0';
	size = (t_point){(int)m->pos_p.x, (int)m->pos_p.y};
	fill(m, size, '0');
	if (m->status == FALSE)
		err_exit(m, MH);
	resize_map(m);
}
