CC			= gcc

NAME		= cub3D

INCLUDES	= ./includes/

MLX			= ./mlx/

# MLX			= ./minilibx-linux/

SRCS		= gnl/get_next_line.c main.c parser/ft_parser.c parser/check_options.c parser/init_options.c parser/utils.c

CFLAGS		= #-Wall -Wextra -Werror

OBJS		= $(SRCS:.c=.o)

LIBS		= -Lmlx -lmlx -framework OpenGL -framework AppKit -lm -Llibft -lft

# LIBS = -Lminilibx-linux/ -lmlx -L/usr/lib -lXext -lX11 -lm -lbsd -Llibft -lft # for linux

all: $(NAME)

%.o:	%.c
		$(CC) -g $(CFLAGS) -I$(INCLUDES) -I$(MLX) -c $< -o $@

$(NAME):	$(OBJS)
		make -C libft/
		$(CC) -g -o $(NAME) -I$(INCLUDES) -I$(MLX) $(OBJS) $(LIBS)

clean:
		make -C libft/ clean
		# @make -C mlx clean
		rm -rf $(OBJS)

fclean:	clean
		make -C libft/ fclean
		# @make -C mlx fclean
		rm -rf $(NAME)

re:		fclean all
