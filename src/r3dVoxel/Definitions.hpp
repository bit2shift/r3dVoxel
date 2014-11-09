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

/*
 * Enumeration type for array types
 * Use only as scalar type, no pointers
 */
struct TypeInfo
{
	char mark;
	char size;
};

bool operator==(const TypeInfo& a, const TypeInfo& b)
{
	short pA = *(short*)&a;
	short pB = *(short*)&b;
	return (pA == pB);
}

/*
 * List of known array types
 */
namespace ArrayTypes
{
	/* signed integers */
	const TypeInfo CHAR    = {0, 1};
	const TypeInfo SHORT   = {0, 2};
	const TypeInfo INT     = {0, 4};
	const TypeInfo LONG    = {0, 8};

	/* unsigned integers */
	const TypeInfo BYTE    = {1, 1};
	const TypeInfo WORD    = {1, 2};
	const TypeInfo DWORD   = {1, 4};
	const TypeInfo QWORD   = {1, 8};

	/* floating point */
	const TypeInfo FLOAT   = {2, 4};
	const TypeInfo DOUBLE  = {2, 8};

	/* pointers */
	const TypeInfo POINTER = {3, sizeof(void*)};
	const TypeInfo ICLASS  = {4, sizeof(void*)};

	/* float vectors */
	const TypeInfo VEC2    = {5, 8};
	const TypeInfo VEC4    = {5, 16};

	/* signed integer vectors */
	const TypeInfo IVEC2   = {6, 8};
	const TypeInfo IVEC4   = {6, 16};

	/* unsigned integer vectors */
	const TypeInfo UVEC2   = {7, 8};
	const TypeInfo UVEC4   = {7, 16};
}
