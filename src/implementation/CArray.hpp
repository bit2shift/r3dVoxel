/*
 * IArray implementation
 */
class CArray : public r3dVoxel::IArray
{
	r3dVoxel::TypeInfo m_type;
	unsigned m_length;
	char* m_array;

public:
	CArray(r3dVoxel::TypeInfo type, unsigned length) : m_type(type), m_length(length)
	{
		m_array = new char[m_type.size * m_length]();
	}

	~CArray()
	{
		//if type is ICLASS, call IClass::release()
		if(m_type == r3dVoxel::ArrayTypes::ICLASS)
		{
			r3dVoxel::IClass** ptr = (r3dVoxel::IClass**)m_array;
			while(m_length--)
				ptr[m_length]->release();
		}

		delete[] m_array;
	}

	///////////////////////////
	//// Interface methods ////
	///////////////////////////

	unsigned length()
	{
		return m_length;
	}

	r3dVoxel::TypeInfo type()
	{
		return m_type;
	}

	void* raw(unsigned index)
	{
		return (m_array + m_type.size * (index % m_length));
	}

	/* Return 0 if type != ICLASS */
	r3dVoxel::IClass*& at(unsigned index)
	{
		if(m_type == r3dVoxel::ArrayTypes::ICLASS)
			return *(r3dVoxel::IClass**)raw(index);
		else
			return *(r3dVoxel::IClass**)r3dVoxel::null;
	}
};

R3VAPI r3dVoxel::IArray* r3vNewArray(r3dVoxel::TypeInfo type, unsigned length)
{
	try
	{
		return new CArray(type, length);
	}
	catch(...){}
	return 0;
}
