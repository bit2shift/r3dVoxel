/*
 * Base class for all interfaces
 * Core of the API
 */

class IClass
{
protected:
	virtual ~IClass(){};

public:
	virtual void Release() = 0;
};
