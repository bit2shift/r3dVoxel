#pragma once

#include <cstddef>
#include <new>

namespace r3dVoxel
{
	namespace memory
	{
		class AllocUtils
		{
			static bool valid(const void* pointer) noexcept;

		public:
			static void* allocate(std::size_t size) noexcept;
			static void deallocate(void* pointer, std::size_t size) noexcept;

			template<typename T>
			static T* create(std::size_t count)
			{
				void* pointer = allocate(count * sizeof(T));
				if(!pointer)
					return nullptr;
				else
					return new(pointer) T[count]{};
			}

			template<typename T>
			static void destroy(void* pointer, std::size_t count)
			{
				if(!valid(pointer))
					return;

				for(std::size_t i = 0; i < count; i++)
					static_cast<T*>(pointer)[i].~T();

				deallocate(pointer, count * sizeof(T));
			}
		};
	}
}
