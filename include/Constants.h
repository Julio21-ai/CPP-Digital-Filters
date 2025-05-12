#pragma once
#include <type_traits>

namespace DigitalFilters::Constants
{
	constexpr long double pi_ld       = 3.141592653589793238462643383279502884L;
	constexpr long double e_ld        = 2.718281828459045235360287471352662498L;
	constexpr long double sqrt2_ld    = 1.414213562373095048801688724209698079L;
	constexpr long double ln2_ld      = 0.693147180559945309417232121458176568L;
	constexpr long double ln10_ld     = 2.302585092994045684017991454684364208L;
	constexpr long double log2e_ld    = 1.442695040888963407359924681001892137L;
	constexpr long double log10e_ld   = 0.434294481903251827651128918916605082L;
	constexpr long double m2sqrtPi_ld = 1.128379167095512573896158903121545172L;

	template <typename T>
		requires std::is_floating_point_v<T>
	constexpr T pi() { return static_cast<T>(pi_ld); }

	template <typename T>
		requires std::is_floating_point_v<T>
	constexpr T e() { return static_cast<T>(e_ld); }

	template <typename T>
		requires std::is_floating_point_v<T>
	constexpr T sqrt2() { return static_cast<T>(sqrt2_ld); }

	template <typename T>
		requires std::is_floating_point_v<T>
	constexpr T ln2() { return static_cast<T>(ln2_ld); }

	template <typename T>
		requires std::is_floating_point_v<T>
	constexpr T ln10() { return static_cast<T>(ln10_ld); }

	template <typename T>
		requires std::is_floating_point_v<T>
	constexpr T log2e() { return static_cast<T>(log2e_ld); }

	template <typename T>
		requires std::is_floating_point_v<T>
	constexpr T log10e() { return static_cast<T>(log10e_ld); }

	template <typename T>
		requires std::is_floating_point_v<T>
	constexpr T two_over_sqrt_pi() { return static_cast<T>(m2sqrtPi_ld); }

	template <typename T>
		requires std::is_floating_point_v<T>
	constexpr T pi_2() { return pi<T>() / static_cast<T>(2); }

	template <typename T>
		requires std::is_floating_point_v<T>
	constexpr T pi_4() { return pi<T>() / static_cast<T>(4); }

	template <typename T>
		requires std::is_floating_point_v<T>
	constexpr T two_pi() { return pi<T>() * static_cast<T>(2); }

	template <typename T>
		requires std::is_floating_point_v<T>
	constexpr T one_over_pi() { return static_cast<T>(1) / pi<T>(); }

	template <typename T>
		requires std::is_floating_point_v<T>
	constexpr T one_over_sqrt2() { return static_cast<T>(1) / sqrt2<T>(); }

}

