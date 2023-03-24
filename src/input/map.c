/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:54:02 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/24 19:14:44 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	resize_map(t_p *m)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	new = ft_calloc(sizeof(char *), m->size.x + 1);
	while (i < m->size.x)
		new[i++] = ft_calloc(sizeof(char), m->size.y + 1);
	i = -1;
	while(++i < m->size.x)
	{
		j = 0;
		while (j <= m->size.y)
		{
			if ((m->map[i][j] != '1' 
			&& m->map[i][j] != '0'
			&& ispos_p(m->map[i][j]) == 0)
			|| j >= (int)ft_strlen(m->map[i]))
				new[i][j] = '1';
			else
				new[i][j] = m->map[i][j];
			j++;
		}
		new[i][j] = '\0';
	}
	free_string_array(m->map);
	m->map = doublcpy(new, m->size.x);
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
	m->size = (t_point){h, w};
}

void	fill(t_p *m, t_point cur, char to_fill)
{
	if (m->fmap[cur.y][cur.x] != '1'
		&& m->fmap[cur.y][cur.x] != '0'
		&& m->fmap[cur.y][cur.x] != 'F')
			m->status = FALSE;
	if (cur.y < 0 || cur.y >= (int)ft_strlen(m->fmap[cur.y])
		|| cur.x < 0 || cur.x >= m->size.y
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
	t_point	size;

	size = (t_point){m->size.x, m->size.y};
	m->fmap = doublcpy(m->map, m->size.y);
	m->fmap[m->pos_p.y][m->pos_p.x] = '0';
	fill(m, m->pos_p, '0');
	if (m->status == FALSE)
		err_exit(m, MH);
	resize_map(m);
}
