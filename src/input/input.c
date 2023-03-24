/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:49:51 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/24 16:48:59 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	get_input(t_m *m)
{
	char	*inpt;
	char	*res;
	char	*i;

	inpt = NULL;
	res = get_next_line(m->fd);
	i = res;
	while (i > 0)
	{
		inpt = ft_strjoin_gnl(inpt, res);
		free(res);
		res = get_next_line(m->fd);
		i = res;
	}
	m->file = ft_strdup(inpt);
	m->map = find_map(m);
	if (!m->map)
		return (free(inpt), FALSE);
	m->input = ft_split(inpt, '\n');
	free(inpt);
	return (TRUE);
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
	if (str[i] == '\0' && num == 1)
		return (TRUE);
	return (FALSE);
}

char	**find_map(t_m *m)
{
	int		i;
	char	*res;
	char	**file;

	i = 0;
	res = ft_strdup("");
	file = ft_split(m->file, '\n');
	while (TRUE)
	{
		if (mapcheck(file[i]) == TRUE)
			break ;
		else if (!file[i + 1])
			return (free_string_array(file), free(res), NULL);
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

char	*find_values(t_m *m)
{
	char	*err;

	err = NULL;
	max_val(m);
	err = find_player(m);
	if (err != NULL)
		return (err);
	m->no = find_texture(m->file, "NO");
	m->so = find_texture(m->file, "SO");
	m->we = find_texture(m->file, "WE");
	m->ea = find_texture(m->file, "EA");
	if (m->no == NULL || m->so == NULL
		|| m->we == NULL || m->ea == NULL)
		return (MT);
	if (TESTING != 1)
		if (check_tex(m))
			return (TF);
	if (find_color(m, m->f, "F") == FALSE
		|| find_color(m, m->c, "C") == FALSE)
		return (MC);
	return (err);
}

void	input_check(t_m *m, int argc, char **argv)
{
	if (argc == 2 && open(argv[1], O_RDONLY) > 0)
	{
		m->fd = open(argv[1], O_RDONLY);
		if (get_input(m) == FALSE)
			err_exit(m, MNF);
		err_exit(m, find_values(m));
		check_map(m);
	}
	else
		ft_printf("Input is a file!\n");
}
