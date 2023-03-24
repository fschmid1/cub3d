/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:39:22 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/24 15:51:54 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	isplayer(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

char	*find_player(t_m *m)
{
	int	i;
	int	j;

	i = -1;
	while (++i < m->size.x)
	{
		j = 0;
		while (m->map[i][j])
		{
			if (isplayer(m->map[i][j]))
			{
				if (m->player.x != -1 || m->player.y != -1)
					return (MP);
				else
					m->player = (t_point){j++, i};
			}
			else if (is_whitespace(m->map[i][j]) || ft_isdigit(m->map[i][j]))
				j++;
			else
				return (IM);
		}
	}
	if (m->player.x == -1 || m->player.y == -1)
		return (NP);
	return (NULL);
}
