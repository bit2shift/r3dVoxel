/*
 * Wrapped array for basic types
 */
template<typename T>
class Array : virtual r3dVoxel::Final
{
private:
	unsigned m_count;
	T* m_array;

public:
	Array(unsigned count)
	{
		m_count = count;
		m_array = new T[count];
	}

	~Array()
	{
		m_count = 0;
		delete[] m_array;
	}

	unsigned length()
	{
		return m_count;
	}

	/* Throws index if out of bounds */
	T& operator[](unsigned index)
	{
		if(index >= m_count)
			throw index;
		else
			return m_array[index];
	}
};
