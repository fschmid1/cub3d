/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_col.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:01:46 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/24 10:30:26 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


void	find_color(t_m *main, int *arr, char *find)
{
	int	i;
	char *res;
	char **conv;

	i = 0;
	res = ft_strdup("");
	while(TRUE)
	{
		if(main->file[i] == find[0] 
			&& is_whitespace(main->file[i + 1]) == TRUE) 
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
	set_color(arr, conv);
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
	int	i;
	char *res;

	i = 0;
	res = ft_strdup("");
	while(file[i] != find[0] && file[i + 1] != find[1])
		i++;
	while(file[i] != '\n' && file[i] != '.')
		i++;
	if (file[i] == '\n')
		printf("ERROR\n");
	while(is_whitespace(file[i]) == FALSE)
		res = str_append(res, file[i++]);
	return(res);
}