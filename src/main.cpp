#include <stdio.h>
#include "r3dVoxel.hpp"

int main(int argv, char **argc)
{
	r3dVoxel::vec4 xx = {1, 0, 0, 1};
	r3dVoxel::vec4 yy = {0, 1, 0, 0};

	r3dVoxel::vec4 zz = r3dVoxel::cross(xx, yy);
	float d = r3dVoxel::dot(xx, xx);
	printf("%g\n", zz[0]);
	printf("%g\n", zz[1]);
	printf("%g\n", zz[2]);
	printf("%g\n", zz[3]);

	printf("d = %g\n", d);
	return 0;
}
