#pragma once

namespace hlslpp
{
	template <bool Test, class T = void>
	struct enable_if {};

	template <class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	template <typename T> struct remove_cv { typedef T type; };
	template <typename T> struct remove_cv<const T> { typedef T type; };
	template <typename T> struct remove_cv<volatile T> { typedef T type; };
	template <typename T> struct remove_cv<const volatile T> { typedef T type; };

	template<typename T> struct is_arithmetic_helper { static const bool value = false; };

	template<> struct is_arithmetic_helper<bool> { static const bool value = true; };
	template<> struct is_arithmetic_helper<char> { static const bool value = true; };
	template<> struct is_arithmetic_helper<signed char> { static const bool value = true; };
	template<> struct is_arithmetic_helper<unsigned char> { static const bool value = true; };
	template<> struct is_arithmetic_helper<wchar_t> { static const bool value = true; };
	template<> struct is_arithmetic_helper<short> { static const bool value = true; };
	template<> struct is_arithmetic_helper<unsigned short> { static const bool value = true; };
	template<> struct is_arithmetic_helper<int> { static const bool value = true; };
	template<> struct is_arithmetic_helper<unsigned int> { static const bool value = true; };
	template<> struct is_arithmetic_helper<long> { static const bool value = true; };
	template<> struct is_arithmetic_helper<unsigned long> { static const bool value = true; };
	template<> struct is_arithmetic_helper<long long> { static const bool value = true; };
	template<> struct is_arithmetic_helper<unsigned long long> { static const bool value = true; };
	template<> struct is_arithmetic_helper<float> { static const bool value = true; };
	template<> struct is_arithmetic_helper<double> { static const bool value = true; };
	template<> struct is_arithmetic_helper<long double> { static const bool value = true; };

	template<typename T>
	struct is_arithmetic : is_arithmetic_helper<typename remove_cv<T>::type> {};

	template<typename T1, typename T2>
	struct is_arithmetic2
	{
		static const bool value = is_arithmetic<T1>::value && is_arithmetic<T2>::value;
	};

	template<typename T1, typename T2, typename T3>
	struct is_arithmetic3
	{
		static const bool value = is_arithmetic<T1>::value && is_arithmetic<T2>::value && is_arithmetic<T3>::value;
	};

	template<typename T1, typename T2, typename T3, typename T4>
	struct is_arithmetic4
	{
		static const bool value = is_arithmetic<T1>::value && is_arithmetic<T2>::value && is_arithmetic<T3>::value && is_arithmetic<T4>::value;
	};

	template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
	struct is_arithmetic8
	{
		static const bool value = 
			is_arithmetic<T1>::value && is_arithmetic<T2>::value && is_arithmetic<T3>::value && is_arithmetic<T4>::value &&
			is_arithmetic<T5>::value && is_arithmetic<T6>::value && is_arithmetic<T7>::value && is_arithmetic<T8>::value;
	};
}