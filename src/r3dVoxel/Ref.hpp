#ifndef R3V_EXPORT

/*
 * A wrapper class for IClass objects
 * Only gets compiled on import
 */
class Ref : virtual r3dVoxel::Final
{
private:
	r3dVoxel::IClass* m_ptr;

public:
	Ref() : m_ptr(0) {}
	Ref(r3dVoxel::IClass* ptr) : m_ptr(ptr) {}

	~Ref()
	{
		if(m_ptr)
			m_ptr->release();
	}

	r3dVoxel::IClass* operator->()
	{
		return m_ptr;
	}
};

#endif
