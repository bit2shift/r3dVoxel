#pragma once

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>

namespace r3dVoxel::util
{
	/*
	 * r3dVoxel's interoperable array
	 */
	template<typename T>
	class Array final
	{
		std::size_t m_len;
		T* m_ptr;

		/* Swap function, used through ADL */
		friend void swap(Array& first, Array& second) noexcept
		{
			using std::swap;
			swap(first.m_len, second.m_len);
			swap(first.m_ptr, second.m_ptr);
		}

	public:
		Array(std::size_t len = 0) : m_len(len), m_ptr(new T[m_len]) {}

		Array(std::initializer_list<T> elems) : Array(elems.size())
		{
			std::copy(elems.begin(), elems.end(), m_ptr);
		}

		Array(const Array& other) : Array(other.m_len)
		{
			std::copy_n(other.m_ptr, m_len, m_ptr);
		}

		Array(Array&& other) : Array()
		{
			swap(*this, other);
		}

		~Array()
		{
			delete[] m_ptr;
		}

		/* Copy|Move'n'Swap idiom */
		Array& operator=(Array other) noexcept
		{
			swap(*this, other);
			return *this;
		}

		/* Length of this array */
		std::size_t length() const noexcept
		{
			return m_len;
		}

		/* Array subscripting */
		T& operator[](std::size_t index)
		{
			if(index < m_len)
				return m_ptr[index % m_len];
			else
				throw std::out_of_range("r3dVoxel::util::Array<T>[index] : index >= length()");
		}

		/* Iterator to the beginning of the array */
		T* begin() noexcept
		{
			return m_ptr;
		}

		/* Const iterator to the beginning of the array */
		const T* begin() const noexcept
		{
			return m_ptr;
		}

		/* Iterator to the end of the array */
		T* end() noexcept
		{
			return (m_ptr + m_len);
		}

		/* Const iterator to the end of the array */
		const T* end() const noexcept
		{
			return (m_ptr + m_len);
		}
	};
}
