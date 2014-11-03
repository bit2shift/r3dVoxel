/*
 * Vector types
 * ivec3/vec3 are redundant, they fit inside ivec4/vec4
 *
 * Note:
 * - "point"  -> (w != 0)
 * - "vector" -> (w == 0)
 */

/* Vector attribute */
#define vec(n)    __attribute__((vector_size(n)))

/* Integer vectors */
typedef int ivec2 vec(8);
typedef int ivec4 vec(16);

/* Float vectors */
typedef float vec2 vec(8);
typedef float vec4 vec(16);

vec4 cross(vec4 a, vec4 b)
{
	//cx = ay*bz - az*by
	//cy = az*bx - ax*bz
	//cz = ax*by - ay*bx
	//cw = aw*bw - aw*bw == 0

	ivec4 m1 = {1, 2, 0, 3};
	ivec4 m2 = {2, 0, 1, 3};
	vec4 c1 = __builtin_shuffle(a, m1) * __builtin_shuffle(b, m2);
	vec4 c2 = __builtin_shuffle(a, m2) * __builtin_shuffle(b, m1);
	return (c1 - c2);
}

float dot(vec4 a, vec4 b)
{
	//d = ax*bx + ay*by + az*bz + aw*bw
	//aw == bw == 0

	ivec4 m1 = {1, 0, 3, 2};
	ivec4 m2 = {2, 3, 0, 1};
	vec4 c = (a * b);
	c += __builtin_shuffle(c, m1); //x+y y+x z+w w+z
	c += __builtin_shuffle(c, m2); //x+z y+w z+x w+y
	return c[0];
}
