/*
 * Wrapped array for basic types
 */

/* FINAL */
template<typename T>
class Array : virtual r3dVoxel::Final
{
private:
	unsigned m_count;
	T* m_array;

public:
	Array(unsigned count)
	{
		this->m_count = count;
		this->m_array = new T[count];
	}

	~Array()
	{
		this->m_count = 0;
		delete[] this->m_array;
	}

	unsigned length()
	{
		return this->m_count;
	}

	/* Throws index if out of bounds */
	T& operator[](unsigned index)
	{
		if(index >= this->m_count)
			throw index;
		else
			return this->m_array[index];
	}
};
