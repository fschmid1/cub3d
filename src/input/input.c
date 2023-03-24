/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:49:51 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/24 12:33:49 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void    get_input(t_m *main)
{
    int     i;
    char	*inpt;
    char	*res;

    i = 0;
	inpt = NULL;
	while ((res = get_next_line(main->fd)) > 0)
	{
		inpt = ft_strjoin_gnl(inpt, res);
		free(res);
	}
	main->file = ft_strdup(inpt);
	main->input = ft_split(inpt, '\n');
	free(inpt);
}

void    testing(t_m *main)
{
	int i = 0;
	printf("NO:%s\n", main->no);
	printf("SO:%s\n", main->so);
	printf("WE:%s\n", main->we);
	printf("EA:%s\n", main->ea);
	printf("F:%s\n", ft_itoa(main->f[0]));
	printf("F:%s\n", ft_itoa(main->f[1]));
	printf("F:%s\n", ft_itoa(main->f[2]));
	printf("C:%s\n", ft_itoa(main->c[0]));
	printf("C:%s\n", ft_itoa(main->c[1]));
	printf("C:%s\n", ft_itoa(main->c[2]));
	while (main->map[i])
		printf("MAP:%s\n", main->map[i++]);
	printf("PLAYER x:%d\n", main->pos_p.x);
	printf("PLAYER y:%d\n", main->pos_p.y);
	printf("\ndone printing\n");
}


int		mapcheck(char *str)
{
	int i;
	int num;

	i = 0;
	while (str[i])
	{
		if (is_whitespace(str[i]))
			i++;
		else if (ft_isdigit(str[i]))
		{
			num = 1;
			i++;
		}
		else
			break ;
	}
	if(str[i] == '\0' && num == 1)
		return (TRUE);
	return (FALSE) ;
}

char	**find_map(t_m *m)
{
	int	i;
	char *res;
	char **file;

	i = 0;
	res = ft_strdup("");
	file = ft_split(m->file, '\n');
	while(TRUE)
	{
		if (mapcheck(file[i]) == TRUE)
			break ;
		else if (!file[i + 1])
		{
			printf("ERROR!\n");
			return (free_string_array(file), free(res), NULL);
		}
		else
			i++;
	}
	while (file[i])
	{
		res = ft_strjoin_gnl(res, file[i++]);
		res = ft_strjoin_gnl(res, "\n");
	}
	free_string_array(file);
	file = ft_split(res, '\n');
	free(res);
	return (file);
}

void	find_values(t_m *main)
{
	main->no = find_texture(main->file, "NO");
	main->so = find_texture(main->file, "SO");
	main->we = find_texture(main->file, "WE");
	main->ea = find_texture(main->file, "EA");
	find_color(main, main->f, "F");
	find_color(main, main->c, "C");
	main->map = find_map(main);
	max_val(main);
	find_player(main);
}

void input_check(t_m *main, int argc, char **argv)
{
    if (argc == 2 && (main->fd = open(argv[1], O_RDONLY)) > 0)
    {
		printf("HERE\n");
    	get_input(main);
		printf("HERE\n");
		find_values(main);
		printf("HERE\n");
		check_map(main);
		printf("HERE\n");
    }
	else
		ft_printf("Input is a file!\n");
}
