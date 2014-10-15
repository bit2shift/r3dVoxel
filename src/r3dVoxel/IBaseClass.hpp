/*
 * Base class for all interfaces
 * Core of the API
 */
class IBaseClass
{
protected:
	virtual ~IBaseClass(){}

public:
	virtual void Release() = 0;
};
