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

	template<typename T, T Value>
	struct integral_constant { static const T value = Value; };

	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;

	template<typename T> struct is_integral_helper : false_type {};

	template<> struct is_integral_helper<bool> : true_type {};
	template<> struct is_integral_helper<char> : true_type {};
	template<> struct is_integral_helper<signed char> : true_type {};
	template<> struct is_integral_helper<unsigned char> : true_type {};
	template<> struct is_integral_helper<wchar_t> : true_type {};
	template<> struct is_integral_helper<short> : true_type {};
	template<> struct is_integral_helper<unsigned short> : true_type {};
	template<> struct is_integral_helper<int> : true_type {};
	template<> struct is_integral_helper<unsigned int> : true_type {};
	template<> struct is_integral_helper<long> : true_type {};
	template<> struct is_integral_helper<unsigned long> : true_type {};
	template<> struct is_integral_helper<long long> : true_type {};
	template<> struct is_integral_helper<unsigned long long> : true_type {};
	
	template<typename T>
	struct is_integral : is_integral_helper<typename remove_cv<T>::type> {};

	template<typename T> struct is_floating_helper : false_type {};

	template<> struct is_floating_helper<float> : true_type {};
	template<> struct is_floating_helper<double> : true_type {};
	template<> struct is_floating_helper<long double> : true_type {};

	template<typename T>
	struct is_floating_point : is_floating_helper<typename remove_cv<T>::type> {};

	template<bool> struct concat;
	template<> struct concat<false> : false_type {};
	template<> struct concat<true> : true_type {};

	template<class T>
	struct is_arithmetic : concat<is_integral<T>::value || is_floating_point<T>::value> {};
}