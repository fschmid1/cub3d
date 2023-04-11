
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
#include <math.h>

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
#define ITE "INVALID TEXTURE EXTENSION"
//-----------------------------------MAP----------------------------------------
#define MNF "MAP NOT FOUND"
#define MH "MAP HAS HOLES"
#define IM "INVALID MAP"
#define ME "MAP EXTENSION NEEDS TO BE \".cub\""
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

typedef struct	s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

//------------------------------------ENUM--------------------------------------
typedef enum e_gstate
{
	START,
	PAUSE,
	GAME,
	DEAD,
	EXIT,
} t_gstate;

//------------------------------------MENU--------------------------------------
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

//------------------------------------INPUT--------------------------------------
typedef struct s_main	t_m;

typedef struct s_parse
{
    //height of map
    //width of map
    int     fd; //file descriptor
    int     status; // return status if map is valid
    char    **input; // full file
    char    *file; // full file as one continous string
    char    **map; // only the map as a char matrix
    int		**intmap; // only the map as a char matrix
    char    **fmap; // only the map for floodfill in struct
    char    *no; //path to NORTH texture
    char    *so; //path to SOUTH texture
    char    *we; //path to WEST texture
    char    *ea; //path to EAST texture
    int     f[3]; //floor color as RGB
    int     c[3]; //sky color as RGB
    t_vec	pos_p; //player position on matrix
    t_vec	size;
	t_m		*main;
} t_p;

//------------------------------------INPUT--------------------------------------
typedef	struct	s_player
{
	t_vec	pos; // player pos
	t_vec	dir; // player dir
}	t_player;

typedef struct	s_camera
{
	t_vec	old_ray_dir;
	t_vec	ray_dir;
	t_vec	ray_pos;
	t_vec	pos;
	t_vec	old_plane;
	t_vec	plane;
	int		map_x;
	int		map_y;
	t_vec	side_dist; // distance to side
	t_vec	delta_dist; // delta ray dir
	t_vec	step; //stepX // stepY
	double	perp_wd; // perp wall dist
	int		hit; 
	int		side; // hit NS OR EW wall?
	double	mspeed; // movement speed
	double	rspeed; // rotation speed
}	t_camera;

typedef struct	s_map
{
	mlx_t		*mlx; //mlx
	mlx_image_t	*img; //initial window
	t_player	*player; //player struct
	int			**map;
	uint32_t	color;
	uint32_t	colorc;
	uint32_t	colorf;
	int			minmap_scale;
}	t_map;

typedef struct	s_texim
{
	mlx_texture_t	*no_tex;
	mlx_image_t		*no_img;
	mlx_texture_t	*so_tex;
	mlx_image_t		*so_img;
	mlx_texture_t	*we_tex;
	mlx_image_t		*we_img;
	mlx_texture_t	*ea_tex;
	mlx_image_t		*ea_img;
} t_texim;

typedef	struct	s_test
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
} t_t;


typedef	struct	s_main
{
	t_t			*t;
	t_texim		*texim;
	t_menu		*men; //menu animation struct
	t_map		*map; //makes the cub 3d
	t_camera	*camera; //camera infos
	t_p			*p; // parsed
	int			window_w; //window width
	int			window_h; //window height
	double		time; //time of current frame
	double		old_time; //time of previous frame
	double		frametime; //time of previous frame
	t_gstate	g_state; //current state
	t_gstate	prev_state; //save of previous state
	int			x; //used for action iteration in game loop
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
//==============================================================================
//----------------------------------GAME/GAME.c---------------------------------
//==============================================================================
void	game_loop(void *param);
// void	game_loop(t_m *m);
void	set_position(t_m *m);
//==============================================================================
//----------------------------------GAME/SETUP.c--------------------------------
//==============================================================================
t_player	*setup_player(t_m *m);
t_camera	*setup_camera(t_m *m);
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
int	**dblcpy_to_int(int **src, int x, int y);
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
void	dprinti(int **str, int x, int y);
void	test_values(t_m *m);
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
//==============================================================================
//--------------------------------------LOAD_WALL.c-------------------------------------
//==============================================================================
void	load_wall(t_m *m);
//==============================================================================
//--------------------------------------MINIMAP.c--------------------------------------
//==============================================================================
void	minimap(t_m *m);
#endif
