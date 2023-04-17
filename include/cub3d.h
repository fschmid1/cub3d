
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
#define TESTING 0
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
#define MSG_P "src/menu/cubed/"
#define MSG_STARTB "src/menu/start/b"
#define MSG_STARTG "src/menu/start/g"
#define MSG_MAPSB "src/menu/maps/b"
#define MSG_MAPSG "src/menu/maps/g"
#define MSG_SETTINGSB "src/menu/settings/b"
#define MSG_SETTINGSG "src/menu/settings/g"
#define BLUE 0
#define GREEN 1
#define MSG_NOF 19

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
	MAPS,
	SETTINGS,
	DEAD,
	EXIT,
} t_gstate;

typedef enum e_gwall
{
	NO,
	SO,
	WE,
	EA,
	DOOR,
} t_gwall;

typedef enum e_entity
{
	WALKABLE,
	WALL,
	PLAYER,
	DOOR_OPEN,
	DOOR_CLOSED,

} t_entity;

//------------------------------------MENU--------------------------------------
typedef struct s_msg
{
	mlx_texture_t **cubed;
	mlx_texture_t ***start;
	mlx_texture_t ***maps;
	mlx_texture_t ***settings;
	int 		num_of_f;
	int			i;
} t_msg;

typedef struct s_menu
{
	mlx_texture_t **tex;
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

typedef struct	s_map
{
	mlx_t		*mlx; //mlx
	mlx_image_t	*img; //initial window
	int			**map;
	uint32_t	color;
	uint32_t	colorc;
	uint32_t	colorf;
	int			minmap_scale;
	mlx_image_t	*fps;
}	t_map;

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
	int		wall;
	bool	is_door;
	t_point	door_pos;
	double	door_dist;
	t_vec	mouse;
} t_t;

typedef	struct	s_main
{
	t_t				*t;
	mlx_texture_t	**tex;
	mlx_texture_t	*cross;
	mlx_texture_t	*gun;
	mlx_texture_t	*muzzle;
	t_menu			*men; //menu animation struct
	t_map			*map; //makes the cub 3d
	t_p				*p; // parsed
	int				window_w; //window width
	int				window_h; //window height
	double			time; //time of current frame
	double			old_time; //time of previous frame
	double			frametime; //time of previous frame
	t_gstate		g_state; //current state
	t_gstate		prev_state; //save of previous state
	int				x; //used for action iteration in game loop
	int				selection; //used for menu cycle
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
//----------------------------------GAME/SETUP.c--------------------------------
//==============================================================================
void	set_dir(t_m *m);
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
int		**dblcpy_to_int(int **src, int x, int y);
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
void	close_menu(t_m *m);
void	open_menu(t_m *m);
//==============================================================================
//--------------------------------------MSG.c-------------------------------------
//==============================================================================
void	draw_msg(t_m *m);
void	msg_tex_to_im(t_m *m);
void	msg_alloc_tex_im(t_m *m);
void	msg_load_textures(mlx_texture_t **dest, char *path, int all);
//==============================================================================
//--------------------------------------LOAD_WALL.c-------------------------------------
//==============================================================================
void	load_wall(t_m *m);
//==============================================================================
//--------------------------------------MINIMAP.c--------------------------------------
//==============================================================================
void	minimap(t_m *m);
void	load_textures(t_m *m, char *path);

#endif
