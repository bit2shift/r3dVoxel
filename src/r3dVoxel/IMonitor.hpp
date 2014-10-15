//FIXME "Position" type
//FIXME what kind of string?
//FIXME "VideoMode" type

/*
 * A rather simple monitor class
 */
class IMonitor : public r3dVoxel::IBaseClass
{
public:
	/* Position on the virtual screen*/
	virtual int getPosition() = 0;

	/* Physical size, in millimeters*/
	virtual int getPhysicalSize() = 0;

	/* Name, encoded as UTF-8 */
	virtual void* getName() = 0;

	/* Currently set video mode */
	virtual void* getVideoMode() = 0;

	/* Supported video modes */
	virtual void* getAllVideoModes() = 0;
};

R3VAPI r3dVoxel::Array< r3dVoxel::Ref<IMonitor> > IMonitor_getAll();
R3VAPI r3dVoxel::Ref<IMonitor> IMonitor_getPrimary();
