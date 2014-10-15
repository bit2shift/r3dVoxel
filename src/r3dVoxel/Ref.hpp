final_tmpl(T, Ref)
{
private:
	T* m_ptr;

public:
	Ref()
	{
		this->m_ptr = new T();
	}

	~Ref()
	{
		delete this->m_ptr;
	}

	operator T*()
	{
		return this->m_ptr;
	}
};
