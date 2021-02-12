#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

// void	test_str(char *str)
// {
// 	*(str + 3) = 'A';
// 	str++;
// }

void	free_test(void *arg)
{
	free(arg);
}

int main()
{
	// int fd = open("d ./path/to_the/south/NO_texture.xpm", O_RDONLY);
	// if (fd < 0)
	// {
	// 	printf("fd -> %d\n", fd);
	// 	return (0);
	// }
	// char *line = (char*)malloc(sizeof(char) * 15);
	// *(line + 14) = '\0';
	// if (read(fd, line, 13) < 0)
	// 	return (0);
	// printf("line -> %s\n", line);
	// free(line);
	// close(fd);

	char **str;
	*str = calloc(5, sizeof(char));
	int i = 0;
	while (i < 4)
		*(*str + i++) = 'b';
	char *s = *str;
	// void *arg = *str;
	*str = "ds";
	free_test(s);
	// printf("str -> %p\n", str);
	// free(*str);
	// printf("arg -> %p\n", *arg);
	// free(arg);
	// sleep(1000);
	// int i;

	// i = 0;
	// while (i < 10)
	// {
	// 	printf("x = %d, y = %d\n", (int)(2 * sin(i) * 100 + 500), (int)(2 * cos(i) * 100 + 500));
	// 	i++;
	// }
	
	// char arr[5] = "1234";
	// char *str = (char*)calloc(5, sizeof(char));

	// i = 0;
	// while (i < 5)
	// 	*(str + i++) = 'b';
	// test_str(arr);
	// printf("%s\n", arr);
	// test_str(str);
	// printf("%s\n", str);
	// free(str);
}