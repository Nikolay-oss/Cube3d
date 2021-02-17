#include <stdio.h>

// (x - x1) / (x2 - x1) = (y - y1) / (y2 - y1)
// A			B				  C
// x(y2 - y1) - y(x1 - x2) - x1y2 + y1x2 = 0
// det = |A1 A2|
//       |B1 B2|

int		isparallel(double a1, double a2, double b1, double b2)
{
	if (!(a1 * b2 - a2 * b1))
		return (1);
	return (0);
}

void	intersect(double p1[4], double p2[4], double *intersect)
{
	double k_line1[3];
	double k_line2[3];
	double det;

	k_line1[0] = p1[3] - p1[1];
	k_line1[1] = p1[0] - p1[2];
	k_line1[2] = -p1[0] * p1[3] + p1[1] * p1[2];
	k_line2[0] = p2[3] - p2[1];
	k_line2[1] = p2[0] - p2[2];
	k_line2[2] = -p2[0] * p2[3] + p2[1] * p2[2];
	det = k_line1[0] * k_line2[1] - k_line2[0] * k_line1[1];
	intersect[0] = (k_line1[1] * k_line2[2] - k_line2[1] * k_line1[2]) / det;
	intersect[1] = (k_line1[0] * k_line1[2] - k_line1[0] * k_line2[2]) / det;
}

int	main()
{
	// double k_line1[3] = {0, 0, 0};
	// double k_line2[3] = {0, 0, 0};

	// k_line1[0] = 0 - 1; // y1 - y2
	// k_line1[1] = 1 - 0; // x2 - x1
	// k_line1[2] = 0 * 1 - 1 * 0; // x1 * y2 - x2 * x1

	// k_line2[0] = 0 - 1;
	// k_line2[1] = 3 - 4;
	// k_line2[2] = 4 * 1 - 0 * 1;

	// double res[2];

	// double det = k_line1[0] * k_line2[1] - k_line2[0] * k_line1[1];
	// res[0] = (k_line1[1] * k_line2[2] - k_line2[1] * k_line1[2]) / det;
	// res[1] = (k_line2[0] * k_line1[2] - k_line1[0] * k_line2[2]) / det;

	double res[2];
	double p1[4] = {0, 0, 1, 1};
	double p2[4] = {3, 1, 4, 0};
	// double p1[4] = {0, 0, 3, 0};
	// double p2[4] = {0, 5, 5, 5};

	if (!isparallel(p1[3] - p1[1], p2[3] - p2[3], p1[0] - p1[2], p2[0] - p2[2]))
	{
		intersect(p1, p2, res);
		printf("x -> %f\ny -> %f\n", res[0], res[1]);
	}
	else
		printf("Parallel\n");
}
