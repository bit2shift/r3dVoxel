#ifndef R3V_EXPORT

/*
 * A wrapper for IClass objects
 * Only gets used on import
 */
template<typename T>
class Ref final
{
private:
	T* m_ptr;

public:
	Ref(T* ptr = nullptr)
	{
		//assign pointer if it's an IClass
		if(dynamic_cast<r3dVoxel::IClass*>(ptr))
			m_ptr = ptr;
		else
			m_ptr = nullptr;
	}

	~Ref()
	{
		if(m_ptr)
			m_ptr->release();
	}

	T* operator->()
	{
		return m_ptr;
	}
};

#endif
