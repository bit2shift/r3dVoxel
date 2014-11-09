/*
 * Defines a monitor's video mode. Valid if refresh is not zero.
 * Example:
 *   SVideoMode vm = {800, 600, 8, 8, 8, 59};
 */
struct SVideoMode
{
	short width;     //screen width in pixels
	short height;    //screen height in pixels
	char red;      //red channel bit depth
	char green;    //green channel bit depth
	char blue;     //blue channel bit depth
	char refresh;  //how fast the screen is refreshed
};
