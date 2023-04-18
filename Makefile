NAME			= cub3D
CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -g -O3

SRC				= $(addprefix $(SRC_DIR), $(SRC_FILES))
SRC_DIR			= src/
SRC_FILES		= main.c

INPUT			= $(addprefix $(INPUT_DIR), $(INPUT_FILES))
INPUT_DIR		= src/input/
INPUT_FILES		= input.c tex_col.c map.c player.c

MLX				= $(addprefix $(MLX_DIR), $(MLX_FILES))
MLX_DIR			= src/mlx/
MLX_FILES		= draw.c free_stuff.c load_wall.c make.c setup.c setup2.c window.c

GAME			= $(addprefix $(GAME_DIR), $(GAME_FILES))
GAME_DIR		= src/game/
GAME_FILES		= calculations.c draw.c game.c minimap.c setup.c triangle.c draw_textures.c

UTILS			= $(addprefix $(UTILS_DIR), $(UTILS_FILES))
UTILS_DIR		= src/utils/
UTILS_FILES		= utils.c error.c

MENU			= $(addprefix $(MENU_DIR), $(MENU_FILES))
MENU_DIR		= src/menu/
MENU_FILES		= tex_img.c msg.c

HDR				= $(addprefix $(HDR_DIR)/, $(HDR_FILES))
HDR_DIR			= include/
HDR_FILES		= cub3d.h

ALL_SRC			=	$(SRC) $(INPUT) $(UTILS) $(MLX) $(GAME) $(MENU)

OBJ_DIR			=	obj/
ALL_OBJ			=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(ALL_SRC))
ALL_OBJ_DIR		=	$(sort $(dir $(ALL_OBJ)))

LINK			= $(MLX42) -Ilibft -Llibft -lft -lglfw -L"$(HOME)/.brew/opt/glfw/lib/"

################################################################################
################################################################################

MLX42			= ./mlx42/build/libmlx42.a
LIBFT			= ./libft/libft.a

GREEN			= "\033[32m"
LGREEN			= "\033[92m"
DEFAULT			= "\033[39m"
RED				= "\033[31m"

################################################################################
################################################################################

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
				@$(CC) $(CFLAGS) -c $< -o $@ -I $(HDR_DIR)
				@echo $(LGREEN)"compiled "$^$(DEFAULT)

$(NAME):		$(LIBFT) $(MLX42) $(ALL_OBJ_DIR) $(ALL_OBJ)
				@$(CC) $(ALL_OBJ) -o $@ $(CFLAGS) $(LINK)
				@echo $(GREEN)Compiled$(DEFAULT) $@

$(MLX42):
				git submodule update --init
				cd mlx42 && cmake -B build && cmake --build build -j4

$(LIBFT):
				git submodule update --init
				cd libft && make && make clean

$(ALL_OBJ_DIR):
	@mkdir -p $(ALL_OBJ_DIR)

################################################################################
################################################################################

LSAN 			= LeakSanitizer
LSANLIB 		= /LeakSanitizer/liblsan.a

lsan: 			CFLAGS += -ILeakSanitizer -Wno-gnu-include-next
lsan:			LINK += -LLeakSanitizer -llsan -lc++
lsan:			fclean $(LSANLIB)
lsan:			all

$(LSAN):
				git clone https://github.com/mhahnFr/LeakSanitizer.git

$(LSANLIB): 	$(LSAN)
				@$(MAKE) -C LeakSanitizer
				@echo $(LGREEN)Compiling$(DEFAULT) $<

################################################################################
################################################################################

all:			$(NAME)

clean:
				@$(RM) -rfv $(patsubst %/,%,$(OBJ_DIR))
				@echo "cleaned $(NAME)"

fclean:
				@make clean
				@$(RM) $(NAME)
				@echo "fcleaned $(NAME)"

re:
				@make fclean
				@make all

run:			$(NAME)
				./$(NAME) maps/huge.cub

lrun:			lsan
				./$(NAME) maps/huge.cub


.PHONY:			all clean fclean re lsan run
.SILENT:		clean
