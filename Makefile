CC			= gcc

NAME		= cub3D

INCLUDES	= ./includes/

SRCS		= gnl/get_next_line.c main.c parser/ft_parser.c parser/check_options.c parser/init_ident.c parser/utils.c

CFLAGS		= #-Wall -Wextra -Werror

OBJS		= $(SRCS:.c=.o)

LIBS		= -Lmlx -lmlx -framework OpenGL -framework AppKit -lm -Llibft -lft

all: $(NAME)

%.o:	%.c
		$(CC) -g $(CFLAGS) -Imlx -Iincludes -c $< -o $@

$(NAME):	$(OBJS)
		make -C libft/
		$(CC) -g -o $(NAME) $(LIBS) $(OBJS)

clean:
		make -C libft/ clean
		# @make -C mlx clean
		rm -rf $(OBJS)

fclean:	clean
		make -C libft/ fclean
		# @make -C mlx fclean
		rm -rf $(NAME)

re:		fclean all
