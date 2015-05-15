/*
 * Defines a monitor's video mode. Valid if refresh is not zero.
 * Example:
 *   SVideoMode vm = {800, 600, 8, 8, 8, 59};
 */
struct SVideoMode final
{
	std::int16_t width;   //screen width in pixels
	std::int16_t height;  //screen height in pixels
	std::int8_t red;      //red channel bit depth
	std::int8_t green;    //green channel bit depth
	std::int8_t blue;     //blue channel bit depth
	std::int8_t refresh;  //how fast the screen is refreshed
};
