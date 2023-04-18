/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:59:04 by pgorner           #+#    #+#             */
/*   Updated: 2023/04/18 11:37:45 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	make_cubed(t_m *m)
{
	unsigned int	i;
	unsigned int	c;
	int				pos;

	make_start(m);
	make_maps(m);
	make_settings(m);
	i = 0;
	c = 0;
	pos = m->window_h / 2 * m->window_w / 2 + 19860;
	while (i++ < (m->men->msg->cubed[m->men->msg->i]->width
			* m->men->msg->cubed[m->men->msg->i]->height))
	{
		if (c == m->men->msg->cubed[m->men->msg->i]->width)
		{
			c = 0;
			pos += m->men->tex[0]->width
				- m->men->msg->cubed[m->men->msg->i]->width;
		}
		c++;
		if (m->men->msg->cubed[m->men->msg->i]->pixels[(i) * 4] != 0)
			ft_memcpy(&m->map->img->pixels[(i + pos) * 4],
				&m->men->msg->cubed[m->men->msg->i]->pixels[(i) * 4], 4);
	}
}

void	make_start(t_m *m)
{
	unsigned int	i;
	unsigned int	c;
	int				pos;
	int				color;

	i = 0;
	c = 0;
	pos = m->window_h / 2 * m->window_w / 1.5 + 46865;
	color = BLUE;
	if (m->selection == 0)
		color = GREEN;
	while (i++ < (m->men->msg->start[color][m->men->msg->i]->width
		* m->men->msg->start[color][m->men->msg->i]->height))
	{
		c++;
		if (c == m->men->msg->start[color][m->men->msg->i]->width)
		{
			c = 0;
			pos += m->men->tex[0]->width
				- m->men->msg->start[color][m->men->msg->i]->width;
		}
		if (m->men->msg->start[color][m->men->msg->i]->pixels[(i) * 4] != 0)
			ft_memcpy(&m->map->img->pixels[(i + pos) * 4],
				&m->men->msg->start[color][m->men->msg->i]->pixels[(i) * 4], 4);
	}
}

void	make_maps(t_m *m)
{
	unsigned int	i;
	unsigned int	c;
	int				pos;
	int				color;

	pos = m->window_h / 2 * m->window_w / 1.3 + 46150;
	color = BLUE;
	if (m->selection == 1)
		color = GREEN;
	i = 0;
	c = 0;
	while (i++ < (m->men->msg->maps[color][m->men->msg->i]->width
		* m->men->msg->maps[color][m->men->msg->i]->height))
	{
		if (c == m->men->msg->maps[color][m->men->msg->i]->width)
		{
			c = 0;
			pos += m->men->tex[0]->width
				- m->men->msg->maps[color][m->men->msg->i]->width;
		}
		c++;
		if (m->men->msg->maps[color][m->men->msg->i]->pixels[(i) * 4] != 0)
			ft_memcpy(&m->map->img->pixels[(i + pos) * 4],
				&m->men->msg->maps[color][m->men->msg->i]->pixels[(i) * 4], 4);
	}
}

void	make_settings(t_m *m)
{
	unsigned int	i;
	unsigned int	c;
	int				pos;
	int				color;

	pos = m->window_h / 2 * m->window_w / 1.15 + 49567;
	color = BLUE;
	if (m->selection == 2)
		color = GREEN;
	i = 0;
	c = 0;
	while (i++ < (m->men->msg->settings[color][m->men->msg->i]->width
		* m->men->msg->settings[color][m->men->msg->i]->height))
	{
		if (c == m->men->msg->settings[color][m->men->msg->i]->width)
		{
			c = 0;
			pos += m->men->tex[0]->width
				- m->men->msg->settings[color][m->men->msg->i]->width;
		}
		c++;
		if (m->men->msg->settings[color][m->men->msg->i]->pixels[i * 4] != 0)
			ft_memcpy(&m->map->img->pixels[(i + pos) * 4], &m->men->msg
				->settings[color][m->men->msg->i]->pixels[i * 4], 4);
	}
}
