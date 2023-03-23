#include "include/cub3d.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_m	*m;

	m = setup_main();
	input_check(m, argc, argv);
	// setup_window(m);
	// register_hooks(m);
	// mlx_loop(m->mlx);
	// mlx_terminate(m->mlx);
	free(m);
	return (0);
}
