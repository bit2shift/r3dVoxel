/*
 * A wrapper class for IClass objects
 */

/* FINAL */
class Ref : virtual r3dVoxel::Final
{
private:
	r3dVoxel::IClass* m_ptr;

public:
	Ref() : m_ptr(0) {}
	Ref(r3dVoxel::IClass* ptr) : m_ptr(ptr) {}

	~Ref()
	{
		if(this->m_ptr)
			this->m_ptr->Release();
	}

	r3dVoxel::IClass* operator->()
	{
		return this->m_ptr;
	}
};