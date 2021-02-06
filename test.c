#include <stdio.h>
#include <math.h>

int main()
{
	int i;

	i = 0;
	while (i < 10)
	{
		printf("x = %d, y = %d\n", (int)(2 * sin(i) * 100 + 500), (int)(2 * cos(i) * 100 + 500));
		i++;
	}
}