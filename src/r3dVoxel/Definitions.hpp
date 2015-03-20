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
 * Copies the "const" modifier from type A to type B
 */
template<typename A, typename B> struct Const               { typedef       B  type; };
template<typename A, typename B> struct Const<const A,  B>  { typedef const B  type; };
template<typename A, typename B> struct Const<const A,  B*> { typedef const B* type; };
template<typename A, typename B> struct Const<const A*, B>  { typedef const B  type; };
template<typename A, typename B> struct Const<const A*, B*> { typedef const B* type; };
