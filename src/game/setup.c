/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 17:33:21 by pgorner           #+#    #+#             */
/*   Updated: 2023/04/17 16:57:59 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	set_dir_ew(t_m *m, char dir)
{
	if (dir == 'W')
	{
		m->t->dirx = -1;
		m->t->diry = 0;
		m->t->planex = 0;
		m->t->planey = -0.66;
	}
	else if (dir == 'E')
	{
		m->t->dirx = 1;
		m->t->diry = 0;
		m->t->planex = 0;
		m->t->planey = 0.66;
	}
}

static void	set_dir_sn(t_m *m, char dir)
{
	if (dir == 'S')
	{
		m->t->dirx = 0;
		m->t->diry = 1;
		m->t->planex = -0.66;
		m->t->planey = 0;
	}
	else if (dir == 'N')
	{
		m->t->dirx = 0;
		m->t->diry = -1;
		m->t->planex = 0.66;
		m->t->planey = 0;
	}
}

void	set_dir(t_m *m)
{
	char	dir;

	dir = m->p->map[(int)m->p->pos_p.y][(int)m->p->pos_p.x];
	set_dir_ew(m, dir);
	set_dir_sn(m, dir);
}
