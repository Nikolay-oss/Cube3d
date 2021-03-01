#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
// #include "libft.h"
// #include "get_next_line.h"

#define mapWidth	24
#define mapHeight	24

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,2,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

typedef	struct	s_point
{
	int			x;
	int			y;
}				t_point;

int	main()
{
	t_point	plr_pos;
	t_point ray_pos;
	double	fov = M_PI / 3; // 60 degrees -> (M_PI / 3) * 180 / M_PI
	double	plr_dir = M_PI / 2;

	plr_pos.x = 18;
	plr_pos.y = 20;

	for (double t = 0.0; t < 24; t += 0.5)
	{
		ray_pos.x = plr_pos.x + t * cos(plr_dir);
		ray_pos.y = plr_pos.y + t * sin(plr_dir);
		if (worldMap[ray_pos.x][ray_pos.y] == 1)
		{
			double dist = sqrt(pow(ray_pos.x - plr_pos.x, 2) + pow(ray_pos.y - plr_pos.y, 2));
			printf("%lf\n", cos(plr_dir));
			printf("plr_x -> %d\tplr_y -> %d\n", plr_pos.x, plr_pos.y);
			printf("ray_pos_x -> %d\tray_pos_y -> %d\n", ray_pos.x, ray_pos.y);
			printf("dist -> %lf\n", dist);
			break ;
		}
	}
	// printf("%lf\n", 1.5708 * 180 / M_PI);
}


















// int	main()
// {
// 	t_list *lst;
// 	t_node *node;
// 	int fd;
// 	char *line;
// 	int res;

// 	lst = ft_create_lst();
// 	fd = open("maps/map_ex.cub", O_RDONLY);
// 	while ((res = get_next_line(fd, &line)) > -1)
// 	{
// 		ft_push_back(lst, line);
// 		if (!res)
// 			break ;
// 	}
// 	close(fd);
// 	node = lst->head;
// 	while (node)
// 	{
// 		// printf("%d\n", *(int*)(node->content));
// 		// printf("%d\n", (int)node->content);
// 		printf("%s\n", (char*)node->content);
// 		node = node->next;
// 	}
// 	printf("lst size -> |%d|\n", (int)lst->size);
// 	ft_lst_clear(lst, &free);
// 	return (0);
// }











// void	test_str(char *str)
// {
// 	*(str + 3) = 'A';
// 	str++;
// }

// void	free_test(void *arg)
// {
// 	free(arg);
// }

// typedef struct		s_node
// {
// 	void			*content;
// 	struct s_node	*next;
// }					t_node;

// typedef	struct		s_list
// {
// 	t_node			*head;
// 	size_t			size;
// }					t_list;



// int main()
// {
// 	// int fd = open("d ./path/to_the/south/NO_texture.xpm", O_RDONLY);
// 	// if (fd < 0)
// 	// {
// 	// 	printf("fd -> %d\n", fd);
// 	// 	return (0);
// 	// }
// 	// char *line = (char*)malloc(sizeof(char) * 15);
// 	// *(line + 14) = '\0';
// 	// if (read(fd, line, 13) < 0)
// 	// 	return (0);
// 	// printf("line -> %s\n", line);
// 	// free(line);
// 	// close(fd);

// 	// char **str;
// 	// *str = calloc(5, sizeof(char));
// 	// int i = 0;
// 	// while (i < 4)
// 	// 	*(*str + i++) = 'b';
// 	// char *s = *str;
// 	// // void *arg = *str;
// 	// *str = "ds";
// 	// free_test(s);
// 	// printf("str -> %p\n", str);
// 	// free(*str);
// 	// printf("arg -> %p\n", *arg);
// 	// free(arg);
// 	// sleep(1000);
// 	// int i;

// 	// i = 0;
// 	// while (i < 10)
// 	// {
// 	// 	printf("x = %d, y = %d\n", (int)(2 * sin(i) * 100 + 500), (int)(2 * cos(i) * 100 + 500));
// 	// 	i++;
// 	// }
	
// 	// char arr[5] = "1234";
// 	// char *str = (char*)calloc(5, sizeof(char));

// 	// i = 0;
// 	// while (i < 5)
// 	// 	*(str + i++) = 'b';
// 	// test_str(arr);
// 	// printf("%s\n", arr);
// 	// test_str(str);
// 	// printf("%s\n", str);
// 	// free(str);
// }