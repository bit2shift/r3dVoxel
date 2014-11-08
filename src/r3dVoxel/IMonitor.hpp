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
	virtual r3dVoxel::math::uvec2 getPhysicalSize() = 0;

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
	 * Note: SVideoMode::valid defines its validity
	 */
	virtual const r3dVoxel::SVideoMode getVideoMode() = 0;

	/*
	 * Supported video modes
	 * Returns: array, NULL if it fails
	 * Note: The array length is (count + 1), with count as
	 *   the number of video modes.
	 * Note: The last element has SVideoMode::valid = 0
	 */
	virtual const r3dVoxel::SVideoMode* getAllVideoModes() = 0;
};
