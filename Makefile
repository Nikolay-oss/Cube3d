CC			= gcc

NAME		= cub3D

INCLUDES	= ./includes/

# MLX			= ./mlx/

MLX			= ./minilibx-linux/

PARS_DIR	= ./parser/

CUBE_DIR	= ./ft_cube/

GAME_DIR	= ./ft_cube/game_control/

RAYCAST_DIR	= ./ft_cube/raycast/

SRCS		= gnl/get_next_line.c main.c $(PARS_DIR)ft_parser.c $(PARS_DIR)check_options.c $(PARS_DIR)init_options.c \
			  $(PARS_DIR)utils.c $(PARS_DIR)map_parser.c	  $(CUBE_DIR)ft_cube.c			$(GAME_DIR)ft_events.c \
			  $(CUBE_DIR)ft_paint.c	$(RAYCAST_DIR)draw_wall.c	$(RAYCAST_DIR)ft_raycast.c	$(GAME_DIR)player_control.c \
			  $(GAME_DIR)player_rotate.c	destroy_memory/destroy_mem.c

CFLAGS		= #-Wall -Wextra -Werror

OBJS		= $(SRCS:.c=.o)

# LIBS		= -L. -lmlx -framework OpenGL -framework AppKit -lm -Llibft -lft

LIBS = -Lminilibx-linux/ -lmlx -L/usr/lib -lXext -lX11 -lm -lbsd -Llibft -lft # for linux

all:	$(NAME)

%.o:	%.c
		$(CC) -g $(CFLAGS) -I$(INCLUDES) -I$(MLX) -c $< -o $@

$(NAME):	$(OBJS)
		make -C libft/
		# make -C $(MLX)
		# mv $(MLX)/libmlx.dylib .
		$(CC) -g -o $(NAME) $(CFLAGS) -O2 -I$(INCLUDES) -I$(MLX) $(OBJS) $(LIBS)

clean:
		make -C libft/ clean
		# @make -C mlx clean
		rm -rf $(OBJS)

fclean:	clean
		make -C libft/ fclean
		# @make -C mlx fclean
		rm -rf $(NAME)

re:		fclean all
