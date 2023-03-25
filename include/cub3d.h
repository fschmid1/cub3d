/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:31:15 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/25 14:04:01 by pgorner          ###   ########.fr       */
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
#define TESTING 1
#define TRUE 1
#define FALSE 0
//---------------------------------TEX/COL--------------------------------------
#define MT "MISSING TEXTURE"
#define MC "MISSING COLOR"
#define MV "MISSING VALUES"
#define TF "TEXTURE FILE INACCESSIBLE"
//-----------------------------------MAP----------------------------------------
#define MNF "MAP NOT FOUND"
#define MH "MAP HAS HOLES"
#define IM "INVALID MAP"
//---------------------------------PLAYER---------------------------------------
#define MP "MULTIPLE STARTING POSITIONS FOUND"
#define NP "NO PLAYER FOUND"
//-------------------------------MENU_SCREEN------------------------------------
#define PNG ".png"
#define MENU 2
#define PATH "src/menu/city/"
#define NUMOFFILES 51
#define SPEED 0.2
// DEFINE NUMBER OF FILES TO NUM OF FILES + 1
// SET PATH TO APPROPRIATE MENU
// "src/menu/dream/" // 1 = dream // NUMOFFILES 3
// "src/menu/city/"  // 2 = city // NUMOFFILES 51
//-------------------------------MENU_MSG------------------------------------
#define MSG_P "src/menu/msg/"
#define MSG_NOF 19
#define MSG_H 270
#define MSG_W 670

//==============================================================================
//----------------------------------STRUCTS-------------------------------------
//==============================================================================
//--------------------------------COORDINATES-----------------------------------
typedef struct s_point {
  int x;
  int y;
} t_point;
//------------------------------------MAIN--------------------------------------

typedef enum e_gstate
{
	START,
	PAUSE,
	GAME,
	DEAD,
	EXIT,
} t_gstate;

typedef	struct	s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct	s_camera
{
	double	x;
	double	y;
	double	ray_dir_x;
	double	ray_dir_y;
}	t_camera;

typedef struct s_main	t_m;

typedef struct s_parse
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
    t_point pos_p;
    t_point size;
	t_m		*main;
} t_p;

typedef struct s_msg
{
	mlx_texture_t **tex;
	mlx_image_t **img;
	int 		num_of_f;
	int			i;
} t_msg;

typedef struct s_menu
{
	mlx_texture_t **tex;
	mlx_image_t **img;
	int 		num_of_f;
	double		t;
	int			i;
	double		speed;
	t_msg		*msg;
} t_menu;

typedef struct	s_map
{
	t_point		size;
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_player	*player;
	double		csize_x;
	double		csize_y;
}	t_map;

typedef	struct	s_main
{
	t_menu		*men;
	t_map		*map;
	t_camera	*camera;
	t_p			*p;
	int			window_w;
	int			window_h;
	double		time;
	double		old_time;
	t_gstate	prev_state;
	t_gstate	g_state;
}	t_m;
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
t_map	*setup_map(t_m *m);
t_p		*setup_parse(t_m *m);
t_menu	*setup_menu(void);
t_msg	*setup_msg(void);
//==============================================================================
//----------------------------------GAME/GAME.c-------------------------------------
//==============================================================================
void	game_loop(t_p *m);
//==============================================================================
//----------------------------------GAME/SETUP.c-------------------------------------
//==============================================================================
t_player	*setup_player(t_m *m);
//==============================================================================
//----------------------------------DRAW.c-------------------------------------
//==============================================================================
void	draw_pixel(t_m *m, int x, int y, uint32_t color);
//==============================================================================
//----------------------------------UTILS.c-------------------------------------
//==============================================================================
int		is_whitespace(char c);
char	*str_append(char *s1, char c);
int		char_check(char c, char *str);
char	**doublcpy(char **src, int size);
//==============================================================================
//----------------------------------ERROR.c-------------------------------------
//==============================================================================
void	safe_exit(t_p *m, char *msg);
void	err_exit(t_p *m, char *msg);
//==============================================================================
//----------------------------------INPUT.c-------------------------------------
//==============================================================================
void	input_check(t_p *m, int argc, char **argv);
char	*find_values(t_p *main);
int		get_input(t_p *main);
char	**find_map(t_p *m);
void	free_t(t_p *m);
//==============================================================================
//---------------------------------TESTING.c------------------------------------
//==============================================================================
void	testing(t_p *main);
void	dprint(char **str);
//==============================================================================
//---------------------------------TEX_COL.c------------------------------------
//==============================================================================
int 	check_tex(t_p *m);
void	set_color(int *arr, char **conv);
char	*find_texture(char *file, char *find);
int		find_color(t_p *main, int *arr, char *find);
//==============================================================================
//----------------------------------PLAYER.c------------------------------------
//==============================================================================
char	*find_player(t_p *m);
int		ispos_p(char c);
//==============================================================================
//-----------------------------------MAP.c--------------------------------------
//==============================================================================
void	check_map(t_p *m);
void	fill(t_p *m, t_point cur, char to_fill);
void	max_val(t_p *m);
//==============================================================================
//-----------------------------------TEX_IMG.c-------------------------------------
//==============================================================================
void	draw_menu(t_m *m);
void	tex_to_im(t_m *m);
void	alloc_tex_im(t_m *m);
void	load_textures(t_m *m, char *path);
//==============================================================================
//--------------------------------------MSG.c-------------------------------------
//==============================================================================
void	draw_msg(t_m *m);
void	msg_tex_to_im(t_m *m);
void	msg_alloc_tex_im(t_m *m);
void	msg_load_textures(t_m *m, char *path);

#endif
