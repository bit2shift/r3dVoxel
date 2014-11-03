/*
 * Wrapped array for IClass objects
 */

using namespace r3dVoxel;

/* FINAL */
class RefArray : virtual Final
{
private:
	un32 m_count;
	Ref* m_array;

public:
	RefArray(un32 count)
	{
		this->m_count = count;
		this->m_array = new Ref[count];
	}

	~RefArray()
	{
		this->m_count = 0;
		delete[] this->m_array;
	}

	un32 length()
	{
		return this->m_count;
	}

	/* Throws index if out of bounds */
	Ref& operator[](un32 index)
	{
		if(index >= this->m_count)
			throw index;
		else
			return this->m_array[index];
	}
};
