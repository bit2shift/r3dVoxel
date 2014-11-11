/*
 * A rather simple monitor class
 */
class IMonitor : public r3dVoxel::IClass
{
public:
	/* Position on the virtual screen */
	virtual r3dVoxel::math::ivec2 getPosition() = 0;

	/*
	 * Physical size, in millimeters
	 * MIGHT NOT BE ACCURATE
	 */
	virtual r3dVoxel::math::ivec2 getPhysicalSize() = 0;

	/*
	 * Name, encoded as UTF-8
	 * The returned string is managed internally
	 * DO NOT FREE IT
	 */
	virtual const char* getName() = 0;

	/*
	 * Currently set video mode
	 * Depends if this monitor has a fullscreen window and
	 *   whether or not it's focused.
	 * Note: zeroed SVideoMode on failure
	 */
	virtual r3dVoxel::SVideoMode getVideoMode() = 0;

	/*
	 * Supported video modes
	 * Returns IBasicArray of SVideoMode
	 * Can be NULL if it fails
	 * Modifying its contents is discouraged
	 */
	virtual r3dVoxel::IBasicArray<r3dVoxel::SVideoMode>* getAllVideoModes() = 0;
};
