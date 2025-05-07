#pragma once
#include <type_traits>
#include <complex>

namespace DigitalFilters
{
	template <typename T,
		typename = std::enable_if_t<std::is_floating_point_v<T>>>
	class FilterUtils
	{
		public :
		#pragma region GainTodB
		static T GainTodB( T magnitude )
		{
			return  static_cast <T>(20.0) * log10( magnitude );
		}
		#pragma endregion

		#pragma region HzToW
		static T HzToW( T freqHz )
		{
			return static_cast<T> (MathConstants::m_pi2 * freqHz);
		}
		#pragma endregion

		static T DecibelToLinearGain( T dB )
		{
			return std::pow( static_cast <T>(10.0),
				std::abs( dB ) / static_cast <T>(20.0) );
		}

		static T PrewarpFrequency( T Fc, T Fs )
		{
			return std::tan( MathConstants::pi * Fc / Fs );
		}

	};
}
