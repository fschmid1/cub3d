/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 17:33:21 by pgorner           #+#    #+#             */
/*   Updated: 2023/04/17 15:15:26 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <stdio.h>

void	set_dir(t_m *m)
{
	char	dir;

	dir = m->p->map[(int)m->p->pos_p.y][(int)m->p->pos_p.x];
	if (dir == 'W')
	{
		m->t->dirx = -1;
		m->t->diry = 0;
	}
	else if (dir == 'E')
	{
		m->t->dirx = 1;
		m->t->diry = 0;
	}
	else if (dir == 'S')
	{
		m->t->dirx = 0;
		m->t->diry = 1;
	}
	else if (dir == 'N')
	{
		m->t->dirx = 0;
		m->t->diry = -1;
	}
}
