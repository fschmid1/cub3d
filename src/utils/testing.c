/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:43:42 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/24 19:40:49 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	testing(t_p *main)
{
	int	i;

	i = 0;
	printf("NO:%s\n", main->no);
	printf("SO:%s\n", main->so);
	printf("WE:%s\n", main->we);
	printf("EA:%s\n", main->ea);
	printf("F:%d\n", main->f[0]);
	printf("F:%d\n", main->f[1]);
	printf("F:%d\n", main->f[2]);
	printf("C:%d\n", main->c[0]);
	printf("C:%d\n", main->c[1]);
	printf("C:%d\n", main->c[2]);
	while (main->map[i])
		printf("MAP:%s\n", main->map[i++]);
	printf("PLAYER x:%d\n", main->pos_p.x);
	printf("PLAYER y:%d\n", main->pos_p.y);
	printf("MAP CHECK: %i (1==MAP OK)\n", main->status);
	printf("\ndone printing\n\n");
}

void	dprint(char **str)
{
	int i = -1;
	while(str[++i])
		printf("%s\n", str[i]);
}