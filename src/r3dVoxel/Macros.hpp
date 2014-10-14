#define base(C)           class C##Base{protected:C##Base(){}}
#define virt(C)           class C:virtual C##Base
#define tmpl(T)           template<typename T>
#define final_class(C)    base(C);virt(C)
#define final_tmpl(T, C)  tmpl(T)base(C);tmpl(T)virt(C)<T>
