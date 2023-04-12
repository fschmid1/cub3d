/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_col.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:01:46 by pgorner           #+#    #+#             */
/*   Updated: 2023/04/12 12:20:14 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	find_color(t_p *main, int *arr, char *find)
{
	int		i;
	char	*res;
	char	**conv;

	i = 0;
	res = ft_strdup("");
	while (TRUE && main->file[i])
	{
		if (main->file[i] == find[0]
			&& is_whitespace(main->file[i + 1]) == TRUE)
			break ;
		i++;
	}
	while (ft_isdigit(main->file[i]) == FALSE && main->file[i])
		i++;
	while (is_whitespace(main->file[i]) == FALSE && main->file[i])
		res = str_append(res, main->file[i++]);
	if (ft_strlen(res) == 0)
		return (free(res), FALSE);
	conv = ft_split(res, ',');
	free(res);
	if (!conv[0] || !conv[1] || !conv[2])
		return (free_string_array(conv), FALSE);
	set_color(arr, conv);
	return (TRUE);
}

void	set_color(int *arr, char **conv)
{
	arr[0] = ft_atoi(conv[0]);
	free(conv[0]);
	arr[1] = ft_atoi(conv[1]);
	free(conv[1]);
	arr[2] = ft_atoi(conv[2]);
	free(conv[2]);
	free(conv);
}

char	*find_texture(char *file, char *find)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_strdup("");
	while (!(file[i] == find[0] && file[i + 1] == find[1]) && file[i])
		i++;
	while (file[i] != '\n' && file[i] != '.' && file[i])
		i++;
	if (file[i] == '\n' || !file[i])
		return (free (res), NULL);
	while (is_whitespace(file[i]) == FALSE && file[i] != '\n')
		res = str_append(res, file[i++]);
	return (res);
}

int	check_tex(t_p *m)
{
	if (access(m->no, X_OK) != 0)
		return	(TRUE);
	if (access(m->so, X_OK) != 0)
		return	(TRUE);
	if (access(m->we, X_OK) != 0)
		return	(TRUE);
	if (access(m->ea, X_OK) != 0)
		return	(TRUE);
	return (FALSE);
}