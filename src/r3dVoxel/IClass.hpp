/*
 * Base class for all interfaces
 * Core of the API
 *
 * Override the destructor in subclasses
 */
class IClass
{
public:
	virtual ~IClass() = 0;
};

IClass::~IClass(){}
