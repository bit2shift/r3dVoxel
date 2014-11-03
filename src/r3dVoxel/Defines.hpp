/*
 * Useful linguistic definitions
 */

#ifdef R3V_EXPORT
#define R3VAPI __declspec(dllexport)
#else
#define R3VAPI __declspec(dllimport)
#endif

typedef char               sn8;
typedef short              sn16;
typedef long               sn32;
typedef long long          sn64;

typedef unsigned char      un8;
typedef unsigned short     un16;
typedef unsigned long      un32;
typedef unsigned long long un64;

/* makeshift 'final' keyword */
class Final
{
protected:
	Final(){};
};
