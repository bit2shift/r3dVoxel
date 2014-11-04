#include "r3dVoxel.hpp"
#include <stdio.h>

int main(int argv, char **argc)
{
	r3dVoxel::math::vec4 xx = {4, 0, 0, 4};
	r3dVoxel::math::vec4 yy = {0, 4, 0, 4};

	r3dVoxel::math::vec4 zz = r3dVoxel::math::norm(r3dVoxel::math::cross(xx, yy));
	printf("%g\n", zz[0]);
	printf("%g\n", zz[1]);
	printf("%g\n", zz[2]);
	printf("%g\n", zz[3]);

	printf("d = %g\n", r3dVoxel::math::dot(zz, zz));
	return 0;
}
