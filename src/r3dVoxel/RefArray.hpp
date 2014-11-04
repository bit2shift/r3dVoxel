/*
 * Wrapped array for IClass objects
 */

/* FINAL */
class RefArray : virtual r3dVoxel::Final
{
private:
	unsigned m_count;
	r3dVoxel::Ref* m_array;

public:
	RefArray(unsigned count)
	{
		this->m_count = count;
		this->m_array = new r3dVoxel::Ref[count];
	}

	~RefArray()
	{
		this->m_count = 0;
		delete[] this->m_array;
	}

	unsigned length()
	{
		return this->m_count;
	}

	/* Throws index if out of bounds */
	r3dVoxel::Ref& operator[](unsigned index)
	{
		if(index >= this->m_count)
			throw index;
		else
			return this->m_array[index];
	}
};
