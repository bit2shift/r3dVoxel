/*
 * Type surrogate
 */
template<typename T> struct type_is {using type = T;};

/*
 * Copies "const" or "volatile" from type A to type B
 */
template<typename A, typename B> struct copy_cv                      : type_is<               B> {};
template<typename A, typename B> struct copy_cv<const          A, B> : type_is<const          B> {};
template<typename A, typename B> struct copy_cv<      volatile A, B> : type_is<      volatile B> {};
template<typename A, typename B> struct copy_cv<const volatile A, B> : type_is<const volatile B> {};
