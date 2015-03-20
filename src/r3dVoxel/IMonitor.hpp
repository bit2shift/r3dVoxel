/*
 * A rather simple monitor class
 */
class IMonitor : public r3dVoxel::IClass
{
public:
	/* Position on the virtual screen */
	virtual r3dVoxel::math::ivec getPosition() const = 0;

	/*
	 * Physical size, in millimeters
	 * MIGHT NOT BE ACCURATE
	 */
	virtual r3dVoxel::math::ivec getPhysicalSize() const = 0;

	/*
	 * Name, encoded as UTF-8
	 * The returned string is managed internally
	 * DO NOT FREE IT
	 */
	virtual const char* getName() const = 0;

	/*
	 * Currently set video mode
	 * Depends if this monitor has a fullscreen window and
	 *   whether or not it's focused.
	 * Note: zeroed SVideoMode on failure
	 */
	virtual r3dVoxel::SVideoMode getVideoMode() const = 0;

	/*
	 * Supported video modes
	 * Returns array of SVideoMode or NULL on failure
	 * Modifying its contents is discouraged
	 */
	virtual r3dVoxel::IByteArray* getAllVideoModes() const = 0;
};
