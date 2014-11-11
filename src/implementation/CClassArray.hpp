/*
 * IClassArray implementation
 */
template<typename T>
class CClassArray : public r3dVoxel::IClassArray<T>
{
	unsigned m_length;
	T** m_array;

public:
	CClassArray(unsigned length) : m_length(length)
	{
		m_array = new T*[m_length]();
	}

	~CClassArray()
	{
		while(m_length--)
			if(m_array[m_length])
				m_array[m_length]->release();

		delete[] m_array;
	}

	///////////////////////////
	//// Interface methods ////
	///////////////////////////

	unsigned length()
	{
		return m_length;
	}

	T*& at(unsigned index)
	{
		return m_array[index % m_length];
	}
};

template<typename T>
r3dVoxel::IClassArray<T>* r3vNewClassArray(unsigned length)
{
	try
	{
		return new CClassArray<T>(length);
	}
	catch(...){}
	return 0;
}
