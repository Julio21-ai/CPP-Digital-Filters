#pragma once
#include <type_traits>
#include <complex>

namespace DigitalFilters::Utils
{
		template <typename T>
			requires std::is_floating_point_v<T>
		constexpr  T DecibelToLinearGain( T dB )
		{
			return std::pow( static_cast <T>(10.0),
				std::abs( dB ) / static_cast <T>(20.0) );
		}

		// Pre-warps the cutoff frequency for analog to digital filter transform
		// (e.g., bilinear transform).
		template <typename T>
			requires std::is_floating_point_v<T>
		constexpr T PrewarpFrequency( T cutoffFrequencyHz, T samplingFrequencyHz )
		{
			return std::tan(
				Constants::pi<T>() * cutoffFrequencyHz / samplingFrequencyHz
			);
		}

		// Converts a linear magnitude (gain) to decibels (dB).
		template <typename T>
			requires std::is_floating_point_v<T>
		constexpr T GainTodB( T magnitude )
		{
			return static_cast<T>(20.0) * std::log10( magnitude );
		}

		// Converts a frequency from Hertz (Hz) to angular frequency (omega, ?)
		// in radians per second.
		template <typename T>
			requires std::is_floating_point_v<T>
		constexpr T HzToOmega( T frequencyHz )
		{
			return Constants::two_pi<T>() * frequencyHz;
		}

		// Converts angular frequency (omega, ?) in radians per second to Hertz (Hz).
		template <typename T>
			requires std::is_floating_point_v<T>
		constexpr T OmegaToHz( T omega )
		{
			return omega / Constants::two_pi<T>();
		}

}
