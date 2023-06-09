/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:50:39 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/24 19:20:16 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	safe_exit(t_p *m, char *msg)
{
	printf("%s\n", msg);
	free_main(m->main);
	exit (0);
}

void	err_exit(t_p *m, char *msg)
{
	if (msg == NULL)
		return ;
	printf("%s\n", msg);
	free_main(m->main);
	exit(0);
}
