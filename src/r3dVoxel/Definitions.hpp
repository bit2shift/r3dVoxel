/*
 * Useful linguistic definitions
 */

#ifdef R3V_EXPORT
#define R3VAPI    extern "C" __declspec(dllexport)
#else
#define R3VAPI    extern "C" __declspec(dllimport)
#endif

/*
 * Makeshift 'final' keyword
 * Use only as base class
 */
class Final
{
protected:
	Final(){}
};
