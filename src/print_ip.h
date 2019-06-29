#pragma once
#include <iostream>
#include <memory.h>

namespace flaber {

	namespace {

		template <typename... Args>
		struct is_all_same;

		template<typename T>
		struct is_all_same<T> : std::true_type {};

		template<typename T>
		struct is_all_same<T, T> : std::true_type {};

		template<typename T, typename U >
		struct is_all_same<T, U> : std::false_type {};

		template<typename T, typename ...Args >
		struct is_all_same<T, T, Args...> : is_all_same<T, Args...> {};

		template<class ...Args>
		constexpr bool is_all_same_v = is_all_same<Args...>::value;

		template<class T>
		void print_ip_part(std::ostream& os, T value)
		{
			if (!std::is_integral_v<T>)
				os << value;
			else
				os << std::char_traits<T>::to_int_type(value);	
		}


		template<int idx, class ...TParams>
		struct  print_tuple
		{
			void operator()(std::ostream& os, const std::tuple<TParams...>& tuple)
			{
				os << std::get<sizeof ... (TParams) - idx>(tuple);

				os << ".";
				print_tuple<idx - 1, TParams...>()(os, tuple);
			}
		};
		template< class ...TParams>
		struct  print_tuple<1, TParams...>
		{
			void operator()(std::ostream& os, const std::tuple<TParams...>& tuple)
			{
				os << std::get<sizeof ... (TParams) - 1>(tuple);
			}
		};
	}

	template <typename CharT>
	void print_ip(std::basic_ostream<CharT>& os, const std::basic_string<CharT>& ip) {
		for (auto it = ip.begin(); it != ip.end(); ++it) {
			os << *it;
		}
	}

	template<template<typename, typename> class ContainerT, typename ValueT, typename AllocT>
	void print_ip(std::ostream& os, const ContainerT<ValueT, AllocT>& t) {
		auto it = t.begin();
		print_ip_part(os, *it);
		++it;
		for (; it != t.end(); ++it) {
			os << ".";
			print_ip_part(os, *it);
		}
	}
	
	template <typename CharT, size_t N>
	void print_ip(std::ostream& os, CharT(&arr)[N]) {
		os << arr;
	}

	template<class IntT,
		typename = std::enable_if_t<std::is_integral_v<IntT>, IntT>>
		void print_ip(std::ostream& os, IntT ip)
	{
		const int s = sizeof(IntT);
		uint8_t arr[s];
		std::memcpy(arr, reinterpret_cast<uint8_t*>(&ip), s);

		print_ip_part(os, arr[s - 1]);
		for (int i = s - 2; i >= 0; --i) {
			os << ".";
			print_ip_part(os, arr[i]);
		}
	}

	template<class ...TParams>
	void print_ip(std::ostream& os, const std::tuple<TParams...>& tuple)
	{
		static_assert(is_all_same_v< TParams...>, "not same types");
		print_tuple< sizeof ... (TParams), TParams...>()(os, tuple);
	}
}
