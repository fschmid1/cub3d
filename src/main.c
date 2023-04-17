/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:52:17 by pgorner           #+#    #+#             */
/*   Updated: 2023/04/17 17:08:39 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdio.h>

void	free_main(t_m *m)
{
	free(m->p->file);
	free_string_array(m->p->map);
	free_string_array(m->p->fmap);
	free_string_array(m->p->input);
	if (m->map->mlx)
	{
		mlx_delete_image(m->map->mlx, m->map->fps);
		mlx_delete_image(m->map->mlx, m->map->img);
	}
	free_map(m);
	free_load_wall(m);
	free_parse(m);
	free_menu(m);
	free(m->t);
	free(m);
}

void	input_check(t_p *m, int argc, char **argv)
{
	if (ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])) == 0)
		err_exit(m, ME);
	if (argc == 2 && open(argv[1], O_RDONLY) > 0)
	{
		m->fd = open(argv[1], O_RDONLY);
		if (get_input(m) == FALSE)
			err_exit(m, MNF);
		err_exit(m, find_values(m));
		check_map(m);
		map_to_int(m);
	}
	else
		err_exit(m, "INPUT IS A FILE");
}

int	main(int argc, char **argv)
{
	t_m		*m;
	mlx_t	*mlx;

	m = setup_main();
	input_check(m->p, argc, argv);
	printf("-------------------INPUT CHECK DONE-------------\n");
	testing(m->p);
	printf("--------------------TESTING DONE----------------\n");
	setup_window(m);
	printf("--------------------WINDOW DONE----------------\n");
	load_wall(m);
	alloc_tex_im(m);
	load_textures(m, PATH);
	printf("--------------------WALLS DONE----------------\n");
	mlx_set_mouse_pos(m->map->mlx, m->window_w / 2, m->window_h / 2);
	draw_msg(m);
	m->map->map = dblcpy_to_int(m->p->intmap, m->p->size.y, m->p->size.x);
	printf("--------------------T SETUP ----------------\n");
	set_position(m);
	register_hooks(m);
	mlx_loop(m->map->mlx);
	mlx = m->map->mlx;
	free_main(m);
	mlx_terminate(mlx);
	return (0);
}
