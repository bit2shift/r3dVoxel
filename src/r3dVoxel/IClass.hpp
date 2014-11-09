/*
 * Base class for all interfaces
 * Core of the API
 */
class IClass
{
protected:
	/* Override the dtor in subclasses when freeing resources */
	virtual ~IClass(){}

public:
	////////////////////////////////
	////  OVERRIDE IS FORBIDDEN ////
	//// THERE CAN ONLY BE ONLY ////
	//// ONE IMPLEMENTATION OF  ////
	////  THIS GLORIOUS METHOD  ////
	////////////////////////////////
	virtual void release();
};
