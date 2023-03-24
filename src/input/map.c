/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:54:02 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/24 11:04:03 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

int	rows(t_m *m, int i, int j, int t)
{
	if (t == 1)
	{
		if (char_check(m->map[i][j], "02") 
			|| is_player(m->map[i][j]))
		{
			if(!m->map[i][j + 1] 
			|| (m->map[i][j + 1] && m->map[i][j + 1] == ' ')) 
                return(TRUE);
		}
		else
			return(FALSE);
	}
	return(FALSE);
}

void check_valid(t_m *m)
{
    int i = -1;
    int j = 0;
    while (m->map[++i])
    {
        while (m->map[i][j] == ' ')
            j++;
        if (m->map[i][j] != '1')
            printf("Error\nCheck map\n");
        while (m->map[i][j])
        {
            if ((m->map[i][j] == '0' || m->map[i][j] == '2' || is_player(m->map[i][j]))
            && (!m->map[i][j + 1] || (m->map[i][j + 1] && m->map[i][j + 1] == ' ')))
                printf("Error\nCheck map\n");
            else if (m->map[i][j] == ' ' && m->map[i][j + 1] && m->map[i][j + 1] != ' ' && m->map[i][j + 1] != '1')
                printf("Error\nCheck map\n");
            j++;
        }
        j = 0;
        while (m->map[i][j])
        {
            if (m->map[i][j] == ' ')
                if ((i > 0 && (int)ft_strlen(m->map[i - 1]) > j && m->map[i - 1][j] != '1' && m->map[i - 1][j] != ' ') ||
                    (m->map[i + 1] && (int)ft_strlen(m->map[i + 1]) > j && m->map[i + 1][j] != '1' && m->map[i + 1][j] != ' '))
                    printf("Error\nCheck map\n");
            if (((i > 0 && (int)ft_strlen(m->map[i - 1]) <= j) || (m->map[i + 1] && (int)ft_strlen(m->map[i + 1]) <= j)) &&
                m->map[i][j] != '1' && m->map[i][j] != ' ')
                printf("Error\nCheck map\n");
            j++;
        }
    }
}

void check_map(t_m *m)
{
	int i;
	
	i = 0;
	max_val(m);
	find_player(m);
	// testing(m);
	printf("MAP RETURN;%i\n", m->size.x);
	check_valid(m);
	printf("MAP RETURN;%i\n", m->status);
}