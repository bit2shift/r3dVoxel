/*
 * Wrapped array for IClass objects
 */
class RefArray : virtual r3dVoxel::Final
{
private:
	unsigned m_count;
	r3dVoxel::Ref* m_array;

public:
	RefArray(unsigned count)
	{
		m_count = count;
		m_array = new r3dVoxel::Ref[count];
	}

	~RefArray()
	{
		m_count = 0;
		delete[] m_array;
	}

	unsigned length()
	{
		return m_count;
	}

	/* Throws index if out of bounds */
	r3dVoxel::Ref& operator[](unsigned index)
	{
		if(index >= m_count)
			throw index;
		else
			return m_array[index];
	}
};
