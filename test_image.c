#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>

#define	width	1280
#define	height	1024
#define	OFFSET	100

typedef struct  s_data
{
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

typedef	struct	s_vars
{
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct	s_all
{
	t_data		img;
	t_data		img_tex;
	t_vars		vars;
}				t_all;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int             win_close(t_all *all) // int keycode, 
{
	mlx_destroy_image(all->vars.mlx, all->img.img);
	mlx_destroy_image(all->vars.mlx, all->img_tex.img);
    mlx_destroy_window(all->vars.mlx, all->vars.win);
	exit(1);
	return (0);
}

void	draw_tex(t_all *all, int w, int h)
{
	int	x;
	int	y;

	x = 0;
	// printf("%d %d\n", w, h);
	while (x < w)
	{
		y = 0;
		while (y < h)
		{
			// int i = 0;
			// int color = 0;
			// while (i < all->img_tex.bits_per_pixel/8)
			// {
			// 	color += *(unsigned int*)(all->img_tex.addr + x*4 + y * 4 + i);
			// 	i++;
			// }
			
			my_mlx_pixel_put(&all->img, x/2 + OFFSET, y/2 + OFFSET, *(unsigned int*)(all->img_tex.addr + (y * all->img_tex.line_length + x * (all->img_tex.bits_per_pixel / 8))));//*(all->img_tex.addr + y + x * 4));//*(all->img_tex.addr + x * all->img_tex.bits_per_pixel + y * all->img_tex.bits_per_pixel));
			// printf("%d ", y * all->img_tex.line_length + x * (all->img_tex.bits_per_pixel / 8));
			// printf("line_len -> %d\n", all->img_tex.line_length);
			y++;
		}
		// printf("\n");
		x++;;
	}
}

void	test(t_all *all)
{
	int		w;
	int		h;

	all->vars.mlx =  mlx_init();
	all->vars.win = mlx_new_window(all->vars.mlx, width, height, "Image testing...");
	all->img.img = mlx_new_image(all->vars.mlx, width, height);
	all->img.addr = mlx_get_data_addr(all->img.img, &all->img.bits_per_pixel, &all->img.line_length, &all->img.endian);
	all->img_tex.img = mlx_xpm_file_to_image(all->vars.mlx, "textures/test.xpm", &w, &h);
	if (all->img.img == NULL)
		exit(1);
	all->img_tex.addr = mlx_get_data_addr(all->img_tex.img, &all->img_tex.bits_per_pixel, &all->img_tex.line_length, &all->img_tex.endian);

	// printf("line_len -> %d\n", all->img.line_length);
	// printf("bits_per_pixel -> %d\n", all->img.bits_per_pixel);	
	// printf("endian -> %d\n", all->img.endian);
	// printf("%d\n", sizeof(*all->img_tex.addr));

	draw_tex(all, w, h);

	mlx_put_image_to_window(all->vars.mlx, all->vars.win, all->img.img, 0, 0);
	// mlx_put_image_to_window(all->vars.mlx, all->vars.win, all->img_tex.img, 0, 0);
}

int	main()
{
	t_all	all;

	test(&all);

	mlx_hook(all.vars.win, 17, 0, &win_close, &all);
	mlx_loop(all.vars.mlx);
}