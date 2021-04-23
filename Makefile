CC			= gcc

NAME		= cub3D

INCLUDES	= ./includes/

MLX			= ./mlx/

# MLX			= ./minilibx-linux/

PARS_DIR	= ./parser/

GNL_DIR		= ./gnl/

MEM_DIR		= ./destroy_memory/

HERRORS_DIR	= ./handler_errors/

CUBE_DIR	= ./ft_cube/

GAME_DIR	= ./ft_cube/game_control/

RAYCAST_DIR	= ./ft_cube/raycast/

SRCS		= main.c							$(GNL_DIR)get_next_line.c		$(PARS_DIR)init_options.c \
			  $(PARS_DIR)ft_parser.c			$(PARS_DIR)check_options.c		$(PARS_DIR)utils.c \
			  $(PARS_DIR)map_parser.c			$(CUBE_DIR)ft_cube.c			$(GAME_DIR)ft_events.c \
			  $(CUBE_DIR)ft_paint.c				$(RAYCAST_DIR)draw_wall.c		$(RAYCAST_DIR)ft_raycast.c \
			  $(GAME_DIR)player_control.c		$(GAME_DIR)player_rotate.c		$(CUBE_DIR)ft_sort.c \
			  $(CUBE_DIR)math_func.c			$(RAYCAST_DIR)ft_sprites.c		$(RAYCAST_DIR)draw_sprite.c \
			  $(PARS_DIR)make_map.c				$(PARS_DIR)map_parser_utils.c	$(CUBE_DIR)data_transfer.c \
			  $(MEM_DIR)destroy_mem.c			$(HERRORS_DIR)handler_errors.c	$(MEM_DIR)destroy_sprite_data.c \
			  $(MEM_DIR)destroy_game_data.c		$(PARS_DIR)check_options_utils.c

CFLAGS		= -Wall -Wextra -Werror

OBJS		= $(SRCS:.c=.o)

LIBS		= -L. -lmlx -framework OpenGL -framework AppKit -lm -Llibft -lft

# LIBS = -Lminilibx-linux/ -lmlx -L/usr/lib -lXext -lX11 -lm -lbsd -Llibft -lft # for linux

all:	$(NAME)
# don't forget about dylib!!!!!!!!!!
%.o:	%.c
		$(CC) -g $(CFLAGS) -I$(INCLUDES) -I$(MLX) -c $< -o $@

$(NAME):	$(OBJS)
		make -C libft/
		make -C $(MLX)
		mv $(MLX)/libmlx.dylib .
		$(CC) -g -o $(NAME) $(CFLAGS) -O2 -I$(INCLUDES) -I$(MLX) $(OBJS) $(LIBS)

clean:
		make -C libft/ clean
		make -C $(MLX) clean
		rm -rf $(OBJS)
		rm -rf libmlx.dylib

fclean:	clean
		make -C libft/ fclean
		# @make -C $(MLX) fclean
		rm -rf $(NAME)

re:		fclean all

t:
	./cub3D maps/map.cub
