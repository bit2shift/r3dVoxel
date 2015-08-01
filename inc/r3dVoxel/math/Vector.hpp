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
#else
#   error This requires a GCC-compatible compiler
#endif

namespace r3dVoxel
{
	namespace math
	{
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
			alignas(16) T x, y, z, w;

			template<typename V, typename = typename std::enable_if<sizeof(V) == 16>::type>
			vec(V simd) noexcept {(*this) = reinterpret_cast<vec&>(simd);}
		};

		/* predefined vectors */
		typedef VEC(float)         fvec;
		typedef VEC(std::int32_t)  ivec;
		typedef VEC(std::uint32_t) uvec;

		inline fvec cross(fvec a, fvec b)
		{
			//cx = ay*bz - az*by
			//cy = az*bx - ax*bz
			//cz = ax*by - ay*bx
			//cw = aw*bw - aw*bw == 0

			/* shuffle party */
			fvec c1 = vec_shuffle(a, 1, 2, 0, 3) * vec_shuffle(b, 2, 0, 1, 3);
			fvec c2 = vec_shuffle(a, 2, 0, 1, 3) * vec_shuffle(b, 1, 2, 0, 3);
			return (c1 - c2);
		}

		inline float dot(fvec a, fvec b)
		{
			//d = ax*bx + ay*by + az*bz + aw*bw
			//aw == bw == 0

			/* first step */
			fvec c = (a * b);

			/* horizontal addition, the shuffle way */
			c += vec_shuffle(c, 1, 0, 3, 2); // x+y     | y+x     | z+w     | w+z     |
			c += vec_shuffle(c, 2, 3, 0, 1); // x+y+z+w | y+x+w+z | z+w+x+y | w+z+y+x |
			return c[0]; //c has the same value all over it
		}

		inline fvec norm(fvec v)
		{
			float d = sqrtf(dot(v, v));
			if(d < 1e-6)
				return (v / fvec{d, d, d, d});
			else
				return fvec{0, 0, 0, 0};
		}
	}
}
