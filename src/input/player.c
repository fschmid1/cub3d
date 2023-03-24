/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:39:22 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/24 11:47:54 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int find_player(t_m *m)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < m->size.x)
	{
        j = 0;
		while(m->map[i][j])
		{
			if (m->map[i][j] == 'N' || m->map[i][j] == 'S'
				|| m->map[i][j] == 'E' || m->map[i][j] == 'W')
				if (m->player.x != -1 || m->player.y != -1)
					return (0);
				else
					m->player = (t_point){j++, i};
            else if (is_whitespace(m->map[i][j])
                || ft_isdigit(m->map[i][j]))
			    j++;
            else
            {
                printf("INVALID MAP\n");
                break ;
            }
		}
		i++;
	}
	if (m->player.x == -1 || m->player.y == -1)
		return (0);
	return (1);
}