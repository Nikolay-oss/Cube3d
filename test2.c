// #include "mlx.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define S_PRESS	0b00000001
#define S1		0b00100000
// #define S_PRESS	0b00000100
#define T	0b11111101
#define UNPRESS 0b11111110

void	test_bitch(int c)
{
	int bitch;

	bitch = c >> 12;
	printf("x -> %d\ty -> %d\n", bitch, c & 0x000FFF);
}

int main()
{
	int x = 1920;
	int y = 4080;
	int c = x;
	c = c << 12;
	c |= y;
	test_bitch(c);
	// unsigned int tmp = S_PRESS;
	// tmp |= S1;
	// printf("%d\t%d\n", tmp, UNPRESS);
	// tmp &= UNPRESS << 2;
	// printf("%d\t%d\n", tmp, S1);
	// printf("%d\t%d\n", S_PRESS, UNPRESS << 1);
}

/*
int create_map()
{
    int i;
    int j;
    char *c;
    void *b;
    void *a;
    void *img;
    int k;
    
    i = 1440;
    j = 900;
    c = "adsfghm";
    a = mlx_init();
    if (a != NULL)
    {
        b = mlx_new_window(a, i, j, c);
        img = mlx_xpm_file_to_image(a, "./textures/texture_1.xpm", 1920, 1080);
       if (b != NULL && img != NULL)
       {

       }
       
       else
        return (-1);
    }
    else
        return (-1);
    mlx_loop(a);
    return(0);    
}

int reader_map()
{
    return(0);
}
*/
/*
int main()
{
    
    if (create_map() == -1)
    {
        return(-1);
    }
    sleep(100);
    return (0);
}
*/
/*
int     main(void)
{
    void    *mlx;
    void    *img;
    char    *relative_path = "./test.xpm";
    int     img_width;
    int     img_height;

    mlx = mlx_init();
    img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
}
*/




// typedef struct  s_data {
//     void        *img;
//     char        *addr;
//     int         bits_per_pixel;
//     int         line_length;
//     int         endian;
// }               t_data;

// void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
//     char    *dst;
    
//     dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
//     *(unsigned int*)dst = color;
// }

// int             main(void)
// {
//     void    *mlx;
//     void    *mlx_win;
//     void    *imege;
//     t_data  img;
//     t_data  img_2;
//     int height = 100;
//     int width  = 100;
//     int a;
//     int b;
//     int color;

//     a = 0;
//     b = 0;
//     mlx = mlx_init();
//     mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
//     img_2.img = mlx_new_image(mlx, 1920, 1080);
//     img_2.addr = mlx_get_data_addr(img_2.img, &img_2.bits_per_pixel, &img_2.line_length, &img_2.endian);
//     img.img = mlx_xpm_file_to_image(mlx, "./textures/redbrick_1.xpm", &(width), &(height));
//     img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
//     while (a < width)
//     {
//         b = 0;
//         while (b < height)
//         {
// 			my_mlx_pixel_put(&img_2, a,  b, *(unsigned int*)(img.addr + (b * img.line_length + a * (img.bits_per_pixel / 8))));
//             //my_mlx_pixel_put(&img_2, (a/2), (b/2), *(unsigned int*)(img.addr + (a * img.line_length + b * (img.bits_per_pixel / 8))));
//             b++;
//         }
//         a++;
//     }
// 	printf("%d\n", 63 * img.line_length + 63 * (img.bits_per_pixel / 8));
//     mlx_put_image_to_window(mlx, mlx_win, img_2.img, 0, 0);
//     mlx_loop(mlx);
//     return (0);
// }
