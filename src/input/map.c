/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:54:02 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/24 17:32:34 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	max_val(t_m *m)
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

void	fill(t_m *m, t_point cur, char to_fill)
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

char	**doublcpy(char **src, int size)
{
	int		i;
	char	**dst;

	i = 0;
	dst = ft_calloc(sizeof(char *), size + 1);
	while (src[i])
	{
		dst[i] = ft_strdup(src[i]);
		i++;
	}
	dst[i] = NULL;
	return (dst);
}

void	check_map(t_m *m)
{
	t_point	size;

	size = (t_point){m->size.x, m->size.y};
	printf("bf\n");
	m->fmap = doublcpy(m->map, m->size.y);
	printf("fmap:%c\n", m->fmap[0][0]);
	printf("af\n");
	m->fmap[m->pos_p.y][m->pos_p.x] = '0';
	fill(m, m->pos_p, '0');
}
