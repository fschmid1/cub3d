/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:34:54 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/24 16:54:04 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

char	**doublcpy(char **src, int size)
{
	int		i;
	char	**dst;

	i = 0;
	dst = ft_calloc(sizeof(char *), size + 1);
	while (src[i])
	{
		dst[i] = ft_strdup(src[i]);
		i++;
	}
	dst[i] = NULL;
	return (dst);
}
