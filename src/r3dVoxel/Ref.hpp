/*
 * A wrapper class for IBaseClass objects
 */
final_tmpl(T, Ref)
{
private:
	T* m_ptr;

public:
	Ref(T* ptr) : m_ptr(ptr) {}

	~Ref()
	{
		if(this->m_ptr)
			this->m_ptr->Release();
	}

	T* operator->()
	{
		return this->m_ptr;
	}
};
