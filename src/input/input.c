/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:49:51 by pgorner           #+#    #+#             */
/*   Updated: 2023/04/17 17:31:56 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	get_input(t_p *m)
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

int	mapcheck(char *str)
{
	int	i;
	int	num;

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

char	**find_map(t_p *m)
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

char	*check_textures(t_p *m)
{
	if (ft_strnstr(m->no, ".png", ft_strlen(m->no)) == 0
		|| ft_strnstr(m->so, ".png", ft_strlen(m->so)) == 0
		|| ft_strnstr(m->we, ".png", ft_strlen(m->we)) == 0
		|| ft_strnstr(m->ea, ".png", ft_strlen(m->ea)) == 0)
		return (ITE);
	if (m->no == NULL || m->so == NULL
		|| m->we == NULL || m->ea == NULL)
		return (MT);
	return (NULL);
}

char	*find_values(t_p *m)
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
	if (TESTING != 1)
	{
	err = check_textures(m);
		if (check_tex(m))
			return (TF);
	}
	if (find_color(m, m->f, "F") == FALSE
		|| find_color(m, m->c, "C") == FALSE)
		return (MC);
	return (err);
}
