/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:43:42 by pgorner           #+#    #+#             */
/*   Updated: 2023/04/11 16:53:39 by pgorner          ###   ########.fr       */
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
	printf("INTMAP:\n");
	dprint(main->map);
	printf("PLAYER x:%f\n", main->pos_p.x);
	printf("PLAYER y:%f\n", main->pos_p.y);
	printf("MAP HEIGHT: Y:%f\n", main->size.y);
	printf("MAP WIDTH: X:%f\n", main->size.x);
	printf("MAP CHECK: %i (1==MAP OK)\n", main->status);
}

void	dprint(char **str)
{
	int i = -1;
	while(str[++i])
		printf("%s\n", str[i]);
}

void	dprinti(int **str, int x, int y)
{
	int i = -1;
	int j = -1;
	while(++i < x)
	{
		j = -1;
		while(++j < y)
		{
			printf("%i", str[i][j]);
		}
		printf("\n");
	}
}

