/*
 * Base class for all interfaces
 * Core of the API
 */
class IClass
{
protected:
	/* Override the destructor in subclasses when freeing resources */
	virtual ~IClass();

public:
	/* Destructor delegate */
	virtual void release();
};
