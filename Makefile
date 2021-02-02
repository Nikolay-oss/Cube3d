CC		= gcc

NAME	= cub3D

SRCS	= shift.c #test_hook.c

CFLAGS	= -Wall -Wextra -Werror

OBJS	= $(SRCS:.c=.o)

LIBS	= -Lmlx -lmlx -framework OpenGL -framework AppKit -lm

all: $(NAME)

%.o:	%.c
	$(CC) -g $(CFLAGS) -Imlx -c $< -o $@

$(NAME):	$(OBJS)
		$(CC) -g -o $(NAME) $(LIBS) $(OBJS)

clean:
		# @make -C mlx clean
		rm -rf $(OBJS)

fclean:	clean
		# @make -C mlx fclean
		rm -rf $(NAME)

re:		fclean all
