/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:54:02 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/23 21:43:57 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

int is_wall(char c) 
{
  return (c == '1');
}

int is_player(char c) 
{
	if (c)
		return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
	return(0);
}

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

// void fill(t_m *m, t_point cur, char to_fill)
// {
// 		m->status += 1;
// 		if ((cur.y < 0 || cur.y >= m->size.y || cur.x < 0 
// 		|| cur.x >= m->size.x || m->map[cur.x][cur.y] != to_fill)&& m->status != 2)
// 		{
// 			printf("1 return\n");
// 			printf("x is %i | y is %i | y.size %i |%c|\n", cur.x, cur.y, m->size.y, m->map[cur.x][cur.y]);
// 				return ;
// 		}
// /* 		else if(m->map[cur.x][cur.y] != to_fill && m->status != 2)
// 		{
// 			printf("INSIDE\n");
// 			if (m->map[cur.x][cur.y] != '1'
// 				&& (m->map[cur.x][cur.y] != 'N'
// 				|| m->map[cur.x][cur.y] != 'S'
// 				|| m->map[cur.x][cur.y] != 'E'
// 				|| m->map[cur.x][cur.y] != 'W'
// 				|| m->map[cur.x][cur.y] != 'F'))
// 			{
// 				printf("map status%i\n", m->status);
// 				printf("RETURNED FALSE AT %i:%i:%c:\n", cur.x, cur.y, m->map[cur.x][cur.y]);
// 				m->status = FALSE;
// 				return ;
// 			}
// 			else
// 				return;
// 		} */
// 	m->map[cur.x][cur.y] = 'F';
// 	fill(m, (t_point){cur.x - 1, cur.y}, to_fill);
// 	fill(m, (t_point){cur.x + 1, cur.y}, to_fill);
// 	fill(m, (t_point){cur.x, cur.y - 1}, to_fill);
// 	fill(m, (t_point){cur.x, cur.y + 1}, to_fill);

// }

int floodfill(t_m *m) 
{
    int seen_up, seen_down, seen_left, seen_right;
    int hole_found = 0;

    int y = 0;
    while (y < m->size.y) {
        size_t x = 0;
        while (x < ft_strlen(m->map[y])) 
		{
            if (m->map[y][x] == '0') {
                x++;
                continue;
            }
				printf("inside\n");
                seen_up = seen_down = seen_left = seen_right = 0;

                // Check if there is a wall to the left of this tile.
                if (x > 0 && m->map[y][x - 1] == '1') {
                    seen_left = 1;
                }

                // Check if there is a wall to the right of this tile.
                if (x < ft_strlen(m->map[y])- 1 && m->map[y][x + 1] == '1') {
                    seen_right = 1;
                }

                // Check if there is a wall above this tile.
                if (y > 0 && m->map[y - 1][x] == '1') {
                    seen_up = 1;
                }

                // Check if there is a wall below this tile.
                if (y < m->size.y - 1 && m->map[y + 1][x] == '1') {
                    seen_down = 1;
                }

                // If we have seen at least two walls that are not connected by
                // a path of floor tiles, there is a disconnected wall.
                if ((seen_up && seen_down && !seen_left && !seen_right) ||
                    (seen_left && seen_right && !seen_up && !seen_down)) {
                    hole_found = 1;
                    break;
                }

            x++;
        }

        if (hole_found) {
            break;
        }

        y++;
    }

    return hole_found;
}

void check_map(t_m *m)
{
	max_val(m);
	find_player(m);
	// testing(m);
	printf("MAP RETURN;%i\n", m->size.x);
	m->status = floodfill(m);
	printf("MAP RETURN;%i\n", m->status);
}