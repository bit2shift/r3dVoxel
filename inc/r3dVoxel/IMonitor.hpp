#pragma once

#include "IClass.hpp"
#include "math/Vector.hpp"
#include "util/Array.hpp"

#include <cstdint>

namespace r3dVoxel
{
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
	class IMonitor : public IClass
	{
	public:
		/* Position on the virtual screen */
		virtual math::ivec getPosition() noexcept = 0;

		/*
		 * Physical size, in millimeters
		 * MIGHT NOT BE ACCURATE!
		 */
		virtual math::ivec getPhysicalSize() noexcept = 0;

		/*
		 * Monitor name, encoded as UTF-8
		 * The returned string is managed internally.
		 */
		virtual const char* getName() noexcept = 0;

		/*
		 * Current video mode
		 * Depends if this monitor has a fullscreen window and
		 *   whether or not it's focused.
		 * Note: zeroed SVideoMode on failure
		 */
		virtual SVideoMode getVideoMode() noexcept = 0;

		/*
		 * Supported video modes
		 * Returns an array of SVideoMode, empty on failure.
		 */
		virtual util::Array<SVideoMode> getAllVideoModes() noexcept = 0;
	};
}
