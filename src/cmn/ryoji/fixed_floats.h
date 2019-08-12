#ifndef __RYOJI_FIXED_FLOATS_H__
#define __RYOJI_FIXED_FLOATS_H__

#include <type_traits>


#ifndef RYOJI_MAKE_CONSTEXPR_FP
#define RYOJI_MAKE_CONSTEXPR_FP(whole, decimal) \
template<typename T> constexpr auto __##whole##p##decimal() { \
	if constexpr (std::is_same_v<T, float>) { return whole##.##decimal##f; }\
	else if constexpr (std::is_same_v<T, double>) { return whole##.##decimal; }\
	else if constexpr (std::is_same_v<T, long double>) { return whole##.##decimal##L; }\
	else static_assert(false);\
}\
template<typename T> constexpr static auto _##whole##p##decimal = __##whole##p##decimal<T>(); 
#endif

#ifndef RYOJI_MAKE_CONSTEXPR_FP_NAMED
#define RYOJI_MAKE_CONSTEXPR_FP_NAMED(name, value) \
template<typename T> constexpr auto _##name() { \
	if constexpr (std::is_same_v<T, float>) { return value ## f; }\
	else if constexpr (std::is_same_v<T, double>) { return value; }\
	else if constexpr (std::is_same_v<T, long double>) { return value ## L; }\
	else static_assert(false);\
}\
template<typename T> constexpr static auto name = _##name<T>();
#endif

#endif