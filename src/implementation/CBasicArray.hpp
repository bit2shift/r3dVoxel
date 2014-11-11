/*
 * IBasicArray implementation
 */
template<typename T>
class CBasicArray : public r3dVoxel::IBasicArray<T>
{
	unsigned m_length;
	T* m_array;

public:
	CBasicArray(unsigned length) : m_length(length)
	{
		m_array = new T[m_length]();
	}

	~CBasicArray()
	{
		delete[] m_array;
	}

	///////////////////////////
	//// Interface methods ////
	///////////////////////////

	unsigned length()
	{
		return m_length;
	}

	T& at(unsigned index)
	{
		return m_array[index % m_length];
	}
};

template<typename T>
r3dVoxel::IBasicArray<T>* r3vNewBasicArray(unsigned length)
{
	try
	{
		return new CBasicArray<T>(length);
	}
	catch(...){}
	return 0;
}
