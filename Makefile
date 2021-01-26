CC		= gcc

NAME	= cub3D

SRCS	= cube3d.c

CFLAGS	= -Wall -Wextra -Werror

OBJS	= $(SRCS:.c=.o)

LIBS	= -Lmlx -lmlx -framework OpenGL -framework AppKit -lm

all: $(NAME)

%.o:	%.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

$(NAME):	$(OBJS)
		$(CC) -o $(NAME) $(LIBS) $(OBJS)

clean:
		# @make -C mlx clean
		rm -rf $(OBJS)

fclean:	clean
		# @make -C mlx fclean
		rm -rf $(NAME)
