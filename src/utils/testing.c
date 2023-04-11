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

void	test_values(t_m *m)
{
	dprinti(m->map->map, m->p->size.x, m->p->size.y);
	printf("----------------PARSE-------------------\n");
	printf("MAP SIZE :X:%f: Y:%f: Z:%f\n", m->p->size.x, m->p->size.y, m->p->size.z);
	printf("MAP PLAYER POS :X:%i: Y:%i: Z:%i\n", (int)m->p->pos_p.x, (int)m->p->pos_p.y, (int)m->p->pos_p.z);
	printf("----------------PLAYER-------------------\n");
	printf("MAP PLAYER POS :X:%f: Y:%f: Z:%f\n", m->map->player->pos.x, m->map->player->pos.y, m->map->player->pos.z);
	printf("MAP PLAYER DIR :X:%f: Y:%f: Z:%f\n", m->map->player->dir.x, m->map->player->dir.y, m->map->player->dir.z);
	printf("----------------NEW LINE-------------------\n");
	printf("MAP SIDE DIST:X:%f: Y:%f: Z:%f\n", m->camera->side_dist.x, m->camera->side_dist.y, m->camera->side_dist.z);
	printf("MAP DELT DIST:X:%f: Y:%f: Z:%f\n", m->camera->delta_dist.x, m->camera->delta_dist.y, m->camera->delta_dist.z);
	printf("MAP STEP:     X:%f: Y:%f: Z:%f\n", m->camera->step.x, m->camera->step.y, m->camera->step.z);
	printf("MAP HIT:     %i\n", m->camera->hit);
	printf("MAP SIDEHIT: %i\n", m->camera->side);
	printf("MAP PERP_WD: %f\n", m->camera->perp_wd);
	printf("-------------------------------------------\n");
	printf("CAM ray_dir:  X:%f: Y:%f: Z:%f\n", m->camera->ray_dir.x, m->camera->ray_dir.y, m->camera->ray_dir.z);
	printf("CAM PLANE:X:%f: Y:%f: Z:%f\n", m->camera->plane.x, m->camera->plane.y, m->camera->plane.z);
	printf("CAM POS:  X:%f: Y:%f: Z:%f\n", m->camera->pos.x, m->camera->pos.y, m->camera->pos.z);
	printf("-------------------------------------------\n");
}
