/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:54:02 by pgorner           #+#    #+#             */
/*   Updated: 2023/04/11 14:27:59 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
	while(++y < m->size.y)
	{
		x = 0;
		while (x < m->size.x)
		{
			if ((!ft_strchr("01dD", m->map[y][x])
			&& ispos_p(m->map[y][x]) == 0)
			|| x >= (int)ft_strlen(m->map[y]))
				new[y][x] = '1';
			else
				new[y][x] = m->map[y][x];
			x++;
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
		|| (m->fmap[0][cur.x] == '0'))
		{
			printf("%i:%i\n", cur.x, cur.y);
			m->status = FALSE;
		}
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
	int i;
	t_point	size;

	i = 0;
	while (i < m->size.y)
		if(m->map[0][i++] == '0')
			err_exit(m, MH);
	size = (t_point){m->size.x, m->size.y};
	m->fmap = doublcpy(m->map, m->size.y);
	// dprint(m->fmap);
	m->fmap[(int)m->pos_p.y][(int)m->pos_p.x] = '0';
	// dprint(m->fmap);
	size = (t_point){(int)m->pos_p.x, (int)m->pos_p.y};
	fill(m, size, '0');
	// dprint(m->fmap);
	if (m->status == FALSE)
		err_exit(m, MH);
	resize_map(m);
}
