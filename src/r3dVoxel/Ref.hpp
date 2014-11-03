/*
 * A wrapper class for IClass objects
 */

using namespace r3dVoxel;

/* FINAL */
class Ref : virtual Final
{
private:
	IClass* m_ptr;

public:
	Ref() : m_ptr(0) {}
	Ref(IClass* ptr) : m_ptr(ptr) {}

	~Ref()
	{
		if(this->m_ptr)
			this->m_ptr->Release();
	}

	IClass* operator->()
	{
		return this->m_ptr;
	}
};
