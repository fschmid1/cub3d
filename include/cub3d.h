#ifndef CUB3D_H
# define CUB3D_H
#include "../libft/src/libft.h"
#include "../mlx42/include/MLX42/MLX42.h"
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

typedef struct s_main
{
    int     h;
    int     w;
    int     fd;
    char    *file;
    char    **input;
    char    *no;
    char    *so;
    char    *we;
    char    *ea;
    int     f[3];
    int     c[3];
	mlx_t		*mlx;
	int			window_w;
	int			window_h;
	mlx_image_t	*img;
} t_m;

// window.c
int		setup_window(t_m *m);
void	register_hooks(t_m *m);

// setup.c
t_m		*setup_main(void);
#endif
