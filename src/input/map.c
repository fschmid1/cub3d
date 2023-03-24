/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:54:02 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/24 12:31:04 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	max_val(t_m *m)
{
	size_t w;
	size_t h;

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

int	char_check(char c, char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(str[i] == c)
			return(TRUE);
		i++;
	}
	return(FALSE);
}

void	fill(t_m *m, t_point size, t_point cur, char to_fill)
{
	if (m->fmap[cur.y][cur.x] != '1'
		&& m->fmap[cur.y][cur.x] != '0'
		&& m->fmap[cur.y][cur.x] != 'F')
			m->status = FALSE;
	if (cur.y < 0 || cur.y >= (int)ft_strlen(m->fmap[cur.y])
		|| cur.x < 0 || cur.x >= m->size.y
		|| m->fmap[cur.y][cur.x] != to_fill)
		return;

	m->fmap[cur.y][cur.x] = 'F';
	fill(m, size, (t_point){cur.x - 1, cur.y}, to_fill);
	fill(m, size, (t_point){cur.x + 1, cur.y}, to_fill);
	fill(m, size, (t_point){cur.x, cur.y - 1}, to_fill);
	fill(m, size, (t_point){cur.x, cur.y + 1}, to_fill);
}

void	doublcpy(char **src, char **dst, int size)
{
	int	i;

	i = 0;
	dst = ft_calloc(sizeof(char *), size + 1);
	while(src[i])
	{
		printf("%i", i);
		dst[i] = ft_strdup(src[i]);
		i++;
	}
	printf("\n");
}

void check_map(t_m *m)
{
	t_point size;
	size = (t_point){m->size.x, m->size.y};
	printf("bf\n");
	doublcpy(m->map, m->fmap, m->size.y);
	printf("fmap:%c\n", m->fmap[0][0]);
	printf("af\n");
	m->fmap[m->pos_p.y][m->pos_p.x] = '0';
	fill(m, size, m->pos_p, '0');
}
