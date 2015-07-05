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

	typedef T simd [[gnu::vector_size(16)]];
	operator T*(){return reinterpret_cast<T*>(this);}
	operator simd&(){return *reinterpret_cast<simd*>(this);}
};

/* predefined vector wrappers */
typedef vec<float>         fvec_t;
typedef vec<std::int32_t>  ivec_t;
typedef vec<std::uint32_t> uvec_t;

/* predefined vectors */
typedef fvec_t::simd fvec;
typedef ivec_t::simd ivec;
typedef uvec_t::simd uvec;

fvec cross(fvec a, fvec b)
{
	//cx = ay*bz - az*by
	//cy = az*bx - ax*bz
	//cz = ax*by - ay*bx
	//cw = aw*bw - aw*bw == 0

	/* shuffle masks */
	ivec m1 = {1, 2, 0, 3};
	ivec m2 = {2, 0, 1, 3};

	/* shuffle party */
	fvec c1 = __builtin_shuffle(a, m1) * __builtin_shuffle(b, m2);
	fvec c2 = __builtin_shuffle(a, m2) * __builtin_shuffle(b, m1);

	return (c1 - c2);
}

float dot(fvec a, fvec b)
{
	//d = ax*bx + ay*by + az*bz + aw*bw
	//aw == bw == 0

	/* shuffle masks */
	ivec m1 = {1, 0, 3, 2};
	ivec m2 = {2, 3, 0, 1};

	/* first step */
	fvec c = (a * b);

	/* horizontal addition, the shuffle way */
	c += __builtin_shuffle(c, m1); // x+y     | y+x     | z+w     | w+z     |
	c += __builtin_shuffle(c, m2); // x+y+z+w | y+x+w+z | z+w+x+y | w+z+y+x |
	return c[0]; //c has the same value all over it
}

fvec norm(fvec v)
{
	/* I like built-in functions */
	return (v / __builtin_sqrtf(dot(v, v)));
}
