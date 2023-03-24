/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:31:15 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/24 12:15:53 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//				██╗  ██╗███████╗ █████╗ ██████╗ ███████╗██████╗
//				██║  ██║██╔════╝██╔══██╗██╔══██╗██╔════╝██╔══██╗
//				███████║█████╗  ███████║██║  ██║█████╗  ██████╔╝
//				██╔══██║██╔══╝  ██╔══██║██║  ██║██╔══╝  ██╔══██╗
//				██║  ██║███████╗██║  ██║██████╔╝███████╗██║  ██║
//				╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═════╝ ╚══════╝╚═╝  ╚═╝

#ifndef CUB3D_H
# define CUB3D_H
#include "../libft/src/libft.h"
#include "../mlx42/include/MLX42/MLX42.h"
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>

//==============================================================================
//-------------------------------DEFINED_VALUES---------------------------------
//==============================================================================
#define TRUE 1
#define FALSE 0
//==============================================================================
//----------------------------------STRUCTS-------------------------------------
//==============================================================================
//--------------------------------COORDINATES-----------------------------------
typedef struct s_point {
  int x;
  int y;
} t_point;
//------------------------------------MAIN--------------------------------------
typedef struct s_main
{
    int     h;
    int     w;
    int     fd;
    int     status;
    char    *file;
    char    **map;
    char    **fmap;
    char    **input;
    char    *no;
    char    *so;
    char    *we;
    char    *ea;
    int     f[3];
    int     c[3];
    t_point player;
    t_point size;
	mlx_t		*mlx;
	int			window_w;
	int			window_h;
	mlx_image_t	*img;
} t_m;
//==============================================================================
//----------------------------------WINDOW.c------------------------------------
//==============================================================================
int		setup_window(t_m *m);
void	register_hooks(t_m *m);
//==============================================================================
//----------------------------------SETUP.c-------------------------------------
//==============================================================================
t_m		*setup_main(void);
void	free_main(t_m *m);
//==============================================================================
//----------------------------------UTILS.c-------------------------------------
//==============================================================================
int	    is_whitespace(char c);
char	*str_append(char *s1, char c);
//==============================================================================
//----------------------------------INPUT.c-------------------------------------
//==============================================================================
void    input_check(t_m *main, int argc, char **argv);
void	find_values(t_m *main);
void    get_input(t_m *main);
void    testing(t_m *main);
//==============================================================================
//---------------------------------TEX_COL.c------------------------------------
//==============================================================================
void	set_color(int *arr, char **conv);
char	*find_texture(char *file, char *find);
void	find_color(t_m *main, int *arr, char *find);
//==============================================================================
//----------------------------------PLAYER.c------------------------------------
//==============================================================================
int     find_player(t_m *m);
//==============================================================================
//-----------------------------------MAP.c--------------------------------------
//==============================================================================
void    check_map(t_m *m);
void	fill(t_m *m, t_point size, t_point cur, char to_fill);
void	max_val(t_m *m);

#endif
