/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:01:43 by pgorner           #+#    #+#             */
/*   Updated: 2023/04/18 13:41:11 by pgorner          ###   ########.fr       */
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

# include"../libft/src/libft.h"
# include"../mlx42/include/MLX42/MLX42.h"
# include<fcntl.h>
# include<limits.h>
# include<stdio.h>
# include<math.h>

//==============================================================================
//-------------------------------DEFINED_VALUES---------------------------------
//==============================================================================
# define TESTING 0
# define TRUE 1
# define FALSE 0
//---------------------------------TEX/COL--------------------------------------
# define MT "MISSING TEXTURE"
# define MC "MISSING COLOR"
# define MV "MISSING VALUES"
# define TF "TEXTURE FILE INACCESSIBLE"
# define ITE "INVALID TEXTURE EXTENSION"
//-----------------------------------MAP----------------------------------------
# define MNF "MAP NOT FOUND"
# define MH "MAP HAS HOLES"
# define IM "INVALID MAP"
# define ME "MAP EXTENSION NEEDS TO BE \".cub\""
//---------------------------------PLAYER---------------------------------------
# define MP "MULTIPLE STARTING POSITIONS FOUND"
# define NP "NO PLAYER FOUND"
//-------------------------------MENU_SCREEN------------------------------------
# define PNG ".png"
# define MENU 2
# define PATH "src/menu/city/"
# define NUMOFFILES 51
# define SPEED 0.2
// DEFINE NUMBER OF FILES TO NUM OF FILES + 1
// SET PATH TO APPROPRIATE MENU
// "src/menu/dream/" // 1 = dream // NUMOFFILES 3
// "src/menu/city/"  // 2 = city // NUMOFFILES 51
//-------------------------------MENU_MSG------------------------------------
# define MSG_P "src/menu/cubed/"
# define MSG_STARTB "src/menu/start/b"
# define MSG_STARTG "src/menu/start/g"
# define MSG_MAPSB "src/menu/maps/b"
# define MSG_MAPSG "src/menu/maps/g"
# define MSG_SETTINGSB "src/menu/settings/b"
# define MSG_SETTINGSG "src/menu/settings/g"
# define BLUE 0
# define GREEN 1
# define MSG_NOF 19

//==============================================================================
//----------------------------------STRUCTS-------------------------------------
//==============================================================================
//--------------------------------COORDINATES-----------------------------------
typedef struct s_point
{
	int	x;
	int	y;
}				t_point;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}				t_vec;

typedef struct s_triangle
{
	t_point	p1;
	t_point	p2;
	t_point	p3;
	double	r;
	t_point	min;
	t_point	max;
}				t_triangle;

//------------------------------------ENUM--------------------------------------
typedef enum e_gstate
{
	START,
	PAUSE,
	GAME,
	MAPS,
	SETTINGS,
	DEAD,
	EXIT,
}			t_gstate;

typedef enum e_gwall
{
	NO,
	SO,
	WE,
	EA,
	DOOR,
}			t_gwall;

typedef enum e_entity
{
	WALKABLE,
	WALL,
	PLAYER,
	DOOR_OPEN,
	DOOR_CLOSED,
}			t_entity;

//------------------------------------MENU--------------------------------------
typedef struct s_msg
{
	mlx_texture_t	**cubed;
	mlx_texture_t	***start;
	mlx_texture_t	***maps;
	mlx_texture_t	***settings;
	int				num_of_f;
	int				i;
}				t_msg;

typedef struct s_menu
{
	mlx_texture_t	**tex;
	int				num_of_f;
	double			t;
	int				i;
	double			speed;
	t_msg			*msg;
}				t_menu;

//------------------------------------INPUT-------------------------------------
typedef struct s_main	t_m;

typedef struct s_parse
{
	int		fd;
	int		status;
	char	**input;
	char	*file;
	char	**map;
	int		**intmap;
	char	**fmap;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f;
	int		c;
	t_vec	pos_p;
	t_vec	size;
	t_m		*main;
}			t_p;

//------------------------------------INPUT-------------------------------------

typedef struct s_map
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			**map;
	uint32_t	color;
	uint32_t	colorc;
	uint32_t	colorf;
	int			minmap_scale;
	mlx_image_t	*fps;
}	t_map;

typedef struct s_test
{
	double	camerax;
	double	raydirx;
	double	raydiry;
	double	posx;
	double	posy;
	int		mapx;
	int		mapy;
	double	dirx;
	double	diry;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	pwd;
	int		hit;
	int		side;
	int		stepx;
	int		stepy;
	double	planex;
	double	planey;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		**map;
	double	time;
	double	old_time;
	double	frametime;
	double	movspeed;
	double	rotspeed;
	double	olddirx;
	double	oldplanex;
	int		wall;
	bool	is_door;
	t_point	door_pos;
	double	door_dist;
	t_vec	mouse;
}				t_t;

typedef struct s_main
{
	t_t				*t;
	mlx_texture_t	**tex;
	mlx_texture_t	*cross;
	mlx_texture_t	*gun;
	mlx_texture_t	*muzzle;
	t_menu			*men;
	t_map			*map;
	t_p				*p;
	int				window_w;
	int				window_h;
	double			time;
	double			old_time;
	double			frametime;
	t_gstate		g_state;
	t_gstate		prev_state;
	int				x;
	int				selection;
	int				firing;
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
t_map	*setup_map(void);
t_p		*setup_parse(t_m *m);
t_menu	*setup_menu(void);
t_msg	*setup_msg(void);
void	free_msg(t_m *m);
//==============================================================================
//----------------------------------GAME/GAME.c---------------------------------
//==============================================================================
void	game_loop(void *param);
void	set_position(t_m *m);
//==============================================================================
//----------------------------------GAME/MOVEMENT.c-----------------------------
//==============================================================================
void	movement(t_m *m);
void	rotate_handler(t_m *m);
//==============================================================================
//----------------------------------GAME/SETUP.c--------------------------------
//==============================================================================
void	set_dir(t_m *m);
//==============================================================================
//----------------------------------DRAW.c--------------------------------------
//==============================================================================
void	draw_pixel(t_m *m, int x, int y, uint32_t color);
//==============================================================================
//----------------------------------UTILS.c-------------------------------------
//==============================================================================
int		is_whitespace(char c);
char	*str_append(char *s1, char c);
int		char_check(char c, char *str);
char	**doublcpy(char **src, int size);
int		**dblcpy_to_int(int **src, int x, int y);
//==============================================================================
//----------------------------------ERROR.c-------------------------------------
//==============================================================================
void	safe_exit(t_p *m, char *msg);
void	err_exit(t_p *m, char *msg);
void	test_values(t_m *m);
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
void	dprinti(int **str, int x, int y);
//==============================================================================
//---------------------------------TEX_COL.c------------------------------------
//==============================================================================
int		check_tex(t_p *m);
int		set_color(char **conv);
char	*find_texture(char *file, char *find);
int		find_color(t_p *main, int *arr, char *find);
//==============================================================================
//----------------------------------PLAYER.c------------------------------------
//==============================================================================
char	*find_player(t_p *m);
int		ispos_p(char c);
//==============================================================================
//----------------------------------triangle.c----------------------------------
//==============================================================================
void	draw_triangle(t_m *m, t_point pos, int size, double dir);
//==============================================================================
//-----------------------------------MAP.c--------------------------------------
//==============================================================================
void	check_map(t_p *m);
void	fill(t_p *m, t_point cur, char to_fill);
void	max_val(t_p *m);
void	map_to_int(t_p *m);
//==============================================================================
//-----------------------------------TEX_IMG.c----------------------------------
//==============================================================================
void	draw_menu(t_m *m);
void	tex_to_im(t_m *m);
void	alloc_tex_im(t_m *m);
void	close_menu(t_m *m);
void	open_menu(t_m *m);
//==============================================================================
//--------------------------------------MSG.c-----------------------------------
//==============================================================================
void	draw_msg(t_m *m);
void	msg_tex_to_im(t_m *m);
void	msg_alloc_tex_im(t_m *m);
void	msg_load_textures(mlx_texture_t **dest, char *path, int all);
//==============================================================================
//--------------------------------------LOAD_WALL.c-----------------------------
//==============================================================================
void	load_wall(t_m *m);
//==============================================================================
//--------------------------------------MINIMAP.c-------------------------------
//==============================================================================
void	minimap(t_m *m);
void	load_textures(t_m *m, char *path);
//==============================================================================
//----------------------------------------MAKE.c--------------------------------
//==============================================================================
void	make_cubed(t_m *m);
void	make_maps(t_m *m);
void	make_start(t_m *m);
void	make_settings(t_m *m);
//==============================================================================
//----------------------------------------FREE_STUFF.c--------------------------
//==============================================================================
void	free_parse(t_m *m);
void	free_msg(t_m *m);
void	free_load_wall(t_m *m);
void	free_map(t_m *m);
void	free_menu(t_m *m);
//==============================================================================
//----------------------------------------CALCULATIONS.c------------------------
//==============================================================================
void	set_values(t_m *m);
void	delta_step(t_m *m);
void	set_side(t_m *m);
void	dda(t_m *m);
void	perp_wd(t_m *m);
//==============================================================================
//----------------------------------------FREE_STUFF.c--------------------------
//==============================================================================
void	draw_ceiling(t_m *m);
int		calc_tex(t_m *m);
void	drawing(t_m *m);
void	draw_textures(t_m *m);
void	draw_lines(t_m *m);
//==============================================================================
//----------------------------------------MOUSE.c-------------------------------
//==============================================================================
void	mouse_hook(double x, double y, void *param);
void	mouse1(double mouse_movement, t_m *m, double ra);
void	mouse2(double mouse_movement, t_m *m, double ra);
#endif
