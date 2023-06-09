/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:39:22 by pgorner           #+#    #+#             */
/*   Updated: 2023/04/18 13:40:34 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ispos_p(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

char	*posp(t_p *m)
{
	if (m->pos_p.x == -1 || m->pos_p.y == -1)
		return (NP);
	return (NULL);
}

char	*find_player(t_p *m)
{
	int	i;
	int	j;

	i = -1;
	while (++i < m->size.y)
	{
		j = 0;
		while (m->map[i][j])
		{
			if (ispos_p(m->map[i][j]))
			{
				if (m->pos_p.x != -1 || m->pos_p.y != -1)
					return (MP);
				else
					m->pos_p = (t_vec){j++, i, 0};
			}
			else if (is_whitespace(m->map[i][j]) || ft_isdigit(m->map[i][j])
					|| ft_strchr("dD012345678", m->map[i][j]))
				j++;
			else
				return (IM);
		}
	}
	return (posp(m));
}
