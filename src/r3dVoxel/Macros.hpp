#define base(C)           class C##Base{protected:C##Base(){}}
#define virt(C)           class C:virtual C##Base
#define final_class(C)    base(C);virt(C)
#define tmpl(T)           template<typename T>
#define final_tmpl(T, C)  base(C);tmpl(T)virt(C)

#ifdef R3V_EXPORT
#define R3VAPI __declspec(dllexport)
#else
#define R3VAPI __declspec(dllimport)
#endif
