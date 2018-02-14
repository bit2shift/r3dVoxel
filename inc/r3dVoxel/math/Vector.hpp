#pragma once

#include <cmath>
#include <cstdint>
#include <type_traits>

#if defined(__GNUG__)
#   define VEC(x) __attribute((vector_size(16))) x
#   if defined(__clang__)
#      define vec_shuffle(v,a,b,c,d) __builtin_shufflevector(v,v,a,b,c,d)
#   else
#      define vec_shuffle(v,a,b,c,d) __builtin_shuffle(v,ivec{a,b,c,d})
#   endif
#   define hop(v,o) {v o##= vec_shuffle(v,1,0,3,2); v o##= vec_shuffle(v,2,3,0,1);}
#else
#   error This requires a GCC-compatible compiler
#endif

namespace r3dVoxel::math
{
	/*
	 * Vector types
	 *
	 * Note:
	 * - "point"  -> (w != 0)
	 * - "vector" -> (w == 0)
	 */
	template<typename T>
	struct alignas(16) vec
	{
		T x, y, z, w;

		template<typename V, typename = std::enable_if_t<sizeof(V) == sizeof(T[4])>>
		vec(V&& simd) noexcept {(*this) = reinterpret_cast<vec&>(simd);}
	};

	/* predefined vectors */
	typedef VEC(float)         fvec;
	typedef VEC(std::int32_t)  ivec;
	typedef VEC(std::uint32_t) uvec;

	inline bool all(ivec v)
	{
		hop(v, &);
		return v[0];
	}

	inline bool any(ivec v)
	{
		hop(v, |);
		return v[0];
	}

	inline fvec cross(fvec a, fvec b)
	{
		//cx = ay*bz - az*by
		//cy = az*bx - ax*bz
		//cz = ax*by - ay*bx
		//cw = aw*bw - aw*bw == 0

		fvec c1 = vec_shuffle(a, 1, 2, 0, 3) * vec_shuffle(b, 2, 0, 1, 3);
		fvec c2 = vec_shuffle(a, 2, 0, 1, 3) * vec_shuffle(b, 1, 2, 0, 3);
		return (c1 - c2);
	}

	inline float dot(fvec a, fvec b)
	{
		//d = ax*bx + ay*by + az*bz + aw*bw
		//aw == bw == 0

		fvec c = (a * b);
		hop(c, +);
		return c[0];
	}

	inline fvec norm(fvec v)
	{
		float d = sqrtf(dot(v, v));
		if(d > 1e-6)
			return (v / fvec{d, d, d, 1});
		else
			return fvec{0, 0, 0, 0};
	}
}
