#include "include/cub3d.h"
#include <stdio.h>

int	main(void)
{
	t_m	*m;

	m = setup_main();
	setup_window(m);
	register_hooks(m);
	mlx_loop(m->mlx);
	mlx_terminate(m->mlx);
	free(m);
	return (0);
}
