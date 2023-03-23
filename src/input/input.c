/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:49:51 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/23 15:40:16 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

char	*str_append(char *s1, char c)
{
	int		i;
	char	*ret;

	if (!c)
		return (s1);
	if (!s1)
		return (ret = ft_calloc(2, sizeof(char)), ret[0] = c, ret);
	i = 0;
	ret = ft_calloc(ft_strlen(s1) + 1 + 1, sizeof(char));
	ft_memcpy(ret, s1, ft_strlen(s1));
	ret[ft_strlen(s1)] = c;
	free(s1);
	return (ret);
}

int	is_whitespace(char c)
{
	if (c == ' ' | c == '\n' | c == '\t' | c == '\v' | c == '\f' | c == '\r')
		return (TRUE);
	else
		return (FALSE);
}

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

char	*find_texture(char *file, char *find)
{
	int	i;
	char *res;

	i = 0;
	res = ft_strdup("");
	while(file[i] != find[0] && file[i + 1] != find[1])
		i++;
	while(file[i] && file[i] != '.')
		i++;
	if (file[i] == '\0')
		printf("ERROR\n");
	while(is_whitespace(file[i]) == FALSE)
		res = str_append(res, file[i++]);
	return(res);
}

void	find_color(t_m *main, int *arr, char *find)
{
	int	i;
	char *res;
	char **conv;

	i = 0;
	res = ft_strdup("");
	while(TRUE)
	{
		if(main->file[i] == find[0] && is_whitespace(main->file[i + 1]) == TRUE) 
			break ;
		else
			i++;
	}
	while(ft_isdigit(main->file[i]) == FALSE)
		i++;
	while(is_whitespace(main->file[i]) == FALSE)
		res = str_append(res, main->file[i++]);
	conv = ft_split(res, ',');
	free(res);
	if (!conv[0] || !conv[1] || !conv[2])
		printf("ERROR\n");
	arr[0] = ft_atoi(conv[0]);
	free(conv[0]);
	arr[1] = ft_atoi(conv[1]);
	free(conv[1]);
	arr[2] = ft_atoi(conv[2]);
	free(conv[2]);
	free(conv);
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

int inputting(int argc, char **argv)
{
    t_m		main;

    if (argc == 2 && (main.fd = open(argv[1], O_RDONLY)) > 0)
    {
    	get_input(&main);
		find_values(&main);
    	testing(&main);
    }
	else
		ft_printf("Input is a file!\n");
    return(0);
}