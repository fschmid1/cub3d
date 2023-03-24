/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:49:51 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/23 17:06:26 by pgorner          ###   ########.fr       */
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
		inpt = ft_strjoin_gnl(inpt, res);
	main->file = ft_strdup(inpt);
	main->input = ft_split(inpt, '\n');
	free(inpt);
}

void    testing(t_m *main)
{
	// int i = 0;

	// while (main->input[i])
	// {
	// 	printf("Input:%i\n", i);
	// 	printf("%s\n", main->input[i]);
	// 	i++;
	// }
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
	printf("\ndone printing\n");
}

void	find_values(t_m *main)
{
	main->no = find_texture(main->file, "NO");
	main->so = find_texture(main->file, "SO");
	main->we = find_texture(main->file, "WE");
	main->ea = find_texture(main->file, "EA");
	find_color(main, main->f, "F");
	find_color(main, main->c, "C");
}

void input_check(t_m *main, int argc, char **argv)
{
    if (argc == 2 && (main->fd = open(argv[1], O_RDONLY)) > 0)
    {
    	get_input(main);
		find_values(main);
    	testing(main);
    }
	else
		ft_printf("Input is a file!\n");
}
