#pragma once

/*
 * Vector types
 *
 * Note:
 * - "point"  -> (w != 0)
 * - "vector" -> (w == 0)
 */
template<typename T>
struct vec
{
	T x, y, z, w;
};

#ifdef __GNUG__
#define VEC(x) __attribute((vector_size(16))) x
#else
#error This requires a GCC-compatible compiler
#endif

/* predefined vectors */
typedef VEC(float)         fvec;
typedef VEC(std::int32_t)  ivec;
typedef VEC(std::uint32_t) uvec;

#ifdef __clang__
#define shuffle(v,a,b,c,d) __builtin_shufflevector(v,v,a,b,c,d)
#else
#define shuffle(v,a,b,c,d) __builtin_shuffle(v,ivec{a,b,c,d})
#endif

fvec cross(fvec a, fvec b)
{
	//cx = ay*bz - az*by
	//cy = az*bx - ax*bz
	//cz = ax*by - ay*bx
	//cw = aw*bw - aw*bw == 0

	/* shuffle party */
	fvec c1 = shuffle(a, 1, 2, 0, 3) * shuffle(b, 2, 0, 1, 3);
	fvec c2 = shuffle(a, 2, 0, 1, 3) * shuffle(b, 1, 2, 0, 3);
	return (c1 - c2);
}

float dot(fvec a, fvec b)
{
	//d = ax*bx + ay*by + az*bz + aw*bw
	//aw == bw == 0

	/* first step */
	fvec c = (a * b);

	/* horizontal addition, the shuffle way */
	c += shuffle(c, 1, 0, 3, 2); // x+y     | y+x     | z+w     | w+z     |
	c += shuffle(c, 2, 3, 0, 1); // x+y+z+w | y+x+w+z | z+w+x+y | w+z+y+x |
	return c[0]; //c has the same value all over it
}

fvec norm(fvec v)
{
	float d = sqrtf(dot(v, v));
	return (v / fvec{d, d, d, d});
}
