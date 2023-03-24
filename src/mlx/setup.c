/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:52:40 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/24 15:52:41 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_m	*setup_main(void)
{
	t_m	*m;

	m = malloc(sizeof(t_m));
	m->mlx = NULL;
	m->img = NULL;
	m->window_h = 1080;
	m->window_w = 1920;
	m->input = NULL;
	m->status = TRUE;
	m->pos_p.x = -1;
  m->pos_p.y = -1;
	m->h = 0;
	m->w = 0;
	m->fd = 0;
	m->file = NULL;
	m->map = NULL;
	m->fmap = NULL;
	m->input = NULL;
	m->no = NULL;
	m->so = NULL;
	m->we = NULL;
	m->ea = NULL;
	return (m);
}

void	free_main(t_m *m)
{
	free(m->file);
	free_string_array(m->map);
	free_string_array(m->fmap);
	free_string_array(m->input);
	free(m->no);
	free(m->so);
	free(m->we);
	free(m->ea);
	free(m);
}
