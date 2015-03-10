/*
 * IByteArray implementation
 */
class CByteArray : public r3dVoxel::IByteArray
{
	unsigned m_length;
	char* m_array;

public:
	CByteArray(unsigned length) : m_length(length)
	{
		m_array = new char[m_length]();
	}

	~CByteArray()
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

	void* pointer()
	{
		return m_array;
	}
};

/*
 * Factory implementation
 * Returns NULL on ctor failure
 */
r3dVoxel::IByteArray* r3vNewByteArray(unsigned length)
{
	try
	{
		return new CByteArray(length);
	}
	catch(...){}
	return 0;
}
