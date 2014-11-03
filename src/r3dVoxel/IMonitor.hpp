//FIXME "VideoMode" type

/*
 * A rather simple monitor class
 */

using namespace r3dVoxel;

class IMonitor : public IClass
{
public:
	/* Position on the virtual screen*/
	virtual int getPosition() = 0;

	/* Physical size, in millimeters*/
	virtual int getPhysicalSize() = 0;

	/* Name, encoded as UTF-8 */
	virtual const char* getName() = 0;

	/* Currently set video mode */
	virtual void* getVideoMode() = 0;

	/* Supported video modes */
	virtual void* getAllVideoModes() = 0;
};
