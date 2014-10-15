final_tmpl(T, Array)
{
private:
	r3dVoxel::un32 m_count;
	T* m_array;

public:
	Array(r3dVoxel::un32 count)
	{
		this->m_count = count;
		this->m_array = new T[count];
	}

	~Array()
	{
		this->m_count = 0;
		delete[] this->m_array;
	}

	r3dVoxel::un32 length()
	{
		return this->m_count;
	}

	/* Throws index if out of bounds */
	T& operator[](r3dVoxel::un32 index)
	{
		if(index >= this->m_count)
			throw index;
		else
			return this->m_array[index];
	}
};
