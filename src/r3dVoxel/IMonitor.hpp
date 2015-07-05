#pragma once

/*
 * Defines a monitor's video mode. Valid if refresh is not zero.
 * Example:
 *   SVideoMode vm = {800, 600, 8, 8, 8, 59};
 */
struct SVideoMode
{
	std::int16_t width;   //screen width in pixels
	std::int16_t height;  //screen height in pixels
	std::int8_t red;      //red channel bit depth
	std::int8_t green;    //green channel bit depth
	std::int8_t blue;     //blue channel bit depth
	std::int8_t refresh;  //how fast the screen is refreshed
};

/*
 * A rather simple monitor class
 */
class IMonitor : public r3dVoxel::IClass
{
public:
	/* Position on the virtual screen */
	virtual r3dVoxel::math::ivec getPosition() = 0;

	/*
	 * Physical size, in millimeters
	 * MIGHT NOT BE ACCURATE
	 */
	virtual r3dVoxel::math::ivec getPhysicalSize() = 0;

	/*
	 * Monitor name, encoded as UTF-8
	 * The returned string is managed internally
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
	 * Returns array of SVideoMode, empty on failure
	 */
	virtual r3dVoxel::Array<r3dVoxel::SVideoMode> getAllVideoModes() = 0;
};
