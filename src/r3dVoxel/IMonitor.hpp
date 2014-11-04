//FIXME "VideoMode" type

/*
 * A rather simple monitor class
 */

class IMonitor : public r3dVoxel::IClass
{
public:
	/* Position on the virtual screen*/
	virtual r3dVoxel::math::ivec2 getPosition() = 0;

	/* Physical size, in millimeters*/
	virtual r3dVoxel::math::ivec2 getPhysicalSize() = 0;

	/* Name, encoded as UTF-8 */
	virtual const char* getName() = 0;

	/* Currently set video mode */
	virtual void* getVideoMode() = 0;

	/* Supported video modes */
	virtual void* getAllVideoModes() = 0;
};
