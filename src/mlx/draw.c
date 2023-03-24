/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 17:32:59 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/24 17:33:00 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_pixel(t_m *m, int x, int y, uint32_t color)
{
	if (x < (int) m->window_w && x > 0)
		if (y < (int) m->window_h && y > 0)
			mlx_put_pixel(m->img, x, y, color);
}
