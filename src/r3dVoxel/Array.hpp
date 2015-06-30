/*
 * r3dVoxel's interoperable array
 */
template<typename T>
class Array final
{
	std::size_t m_num;
	T* m_arr;

public:
	Array() noexcept : m_num(0), m_arr(nullptr) {}

	Array(std::size_t num) : m_num(num)
	{
		m_arr = new T[m_num]();
	}

	Array(std::initializer_list<T> elems) : Array(elems.size())
	{
		std::copy(elems.begin(), elems.end(), m_arr);
	}

	Array(const Array& other) : Array(other.m_num)
	{
		std::copy_n(other.m_arr, other.m_num, m_arr);
	}

	~Array() noexcept
	{
		delete[] m_arr;
	}

	/* Swap function, used through ADL */
	friend void swap(Array& first, Array& second) noexcept
	{
		using std::swap; //triggers ADL
		swap(first.m_num, second.m_num);
		swap(first.m_arr, second.m_arr);
	}

	/* swap() is the above friend on the following two declarations */
	Array(Array&& other) noexcept : Array()
	{
		swap(*this, other);
	}

	/* Copy|Move'n'Swap idiom */
	Array& operator=(Array other) noexcept
	{
		swap(*this, other);
		return *this;
	}

	/* Disable the default copy and move assignments (see above) */
	Array& operator=(const Array&) = delete;
	Array& operator=(Array&&) = delete;

	/* Length of this array */
	std::size_t length() noexcept
	{
		return m_num;
	}

	/* Array subscripting */
	T& operator[](std::size_t index)
	{
		if(index < m_num)
			return m_arr[index];
		else
			throw std::out_of_range("r3dVoxel::Array<T>[index] >>---> index >= length()");
	}
};
