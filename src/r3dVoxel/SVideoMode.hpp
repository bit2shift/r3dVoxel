/*
 * Defines a monitor's video mode
 * Example:
 *   SVideoMode vm = {1, 800, 600, 8, 8, 8, 59};
 */
struct SVideoMode
{
	int valid;     //video mode valid if not 0
	int width;     //screen width in pixels
	int height;    //screen height in pixels
	char red;      //red channel bit depth
	char green;    //green channel bit depth
	char blue;     //blue channel bit depth
	char refresh;  //how fast the screen is refreshed
};
