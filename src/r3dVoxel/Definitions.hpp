/*
 * Useful linguistic definitions
 */

#ifdef R3V_EXPORT
#define R3VAPI __declspec(dllexport)
#else
#define R3VAPI __declspec(dllimport)
#endif

/* makeshift 'final' keyword */
class Final
{
protected:
	Final(){}
};