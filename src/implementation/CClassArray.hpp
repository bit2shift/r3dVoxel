/*
 * IClassArray implementation
 */
class CClassArray : public r3dVoxel::IClassArray
{
	unsigned m_length;
	r3dVoxel::IClass** m_array;

public:
	CClassArray(unsigned length) : m_length(length)
	{
		m_array = new r3dVoxel::IClass*[m_length]();
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

	unsigned length() const
	{
		return m_length;
	}

	r3dVoxel::IClass*& at(unsigned index) const
	{
		return m_array[index % m_length];
	}
};

r3dVoxel::IClassArray* r3vNewClassArray(unsigned length)
{
	try
	{
		return new CClassArray(length);
	}
	catch(...){}
	return 0;
}
