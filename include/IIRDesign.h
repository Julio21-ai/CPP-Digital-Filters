#pragma once
#include "Biquad.h"
#include <vector>
#include <type_traits>

namespace DigitalFilters::IIR
{
	// Functions Parameters:
	//   - peakGain: Peak gain of the filter in Db.
	//   - Fc: Center frequency of the filter in Hz.
	//   - Q: Quality factor of the filter.
	//   - Fs: Sampling frequency in Hz.

	// calculate coefficients for a 1stOrder AllPass filter.
	template <typename T> requires std::is_floating_point_v<T>
	Biquad<T> AllPass1stOrder	( T Fc, T Fs );

	// calculate coefficients for a AllPass filter with Q factor.
	template <typename T> requires std::is_floating_point_v<T>
	Biquad<T>AllPassQ( T Fc, T Q, T Fs );

	// calculate coefficients for a BandPass filter.
	template <typename T> requires std::is_floating_point_v<T>
	Biquad<T>BandPass( T Fc, T Q, T Fs );

	// calculate coefficients for a HighPass filter.
	template <typename T> requires std::is_floating_point_v<T>
	Biquad<T>HighPass( T Fc, T Q, T Fs );

	// calculate coefficients for a HighPass filter.
	template <typename T> requires std::is_floating_point_v<T>
	Biquad<T>HighPass12dbOct( T Fc, T Fs );

	// calculate coefficients for a 1stOrder HighPass1stOrder filter.
	template <typename T> requires std::is_floating_point_v<T>
	Biquad<T>HighPass1stOrder( T Fc, T Fs );

	// calculate coefficients for a HighPass filter.
	template <typename T> requires std::is_floating_point_v<T>
	Biquad<T>HighShelf( T peakGain, T Fc, T Fs );

	// calculate coefficients for a 1stOrder HighShelf filter.
	template <typename T> requires std::is_floating_point_v<T>
	Biquad<T>HighShelf1stOrder( T peakGain, T Fc, T Fs );

	// calculate coefficients for a HighPass filter with Q factor.
	template <typename T> requires std::is_floating_point_v<T>
	Biquad<T>HighShelfQ( T peakGain, T Fc, T Q, T Fs );

	// calculate coefficients for a LowPass filter.
	template <typename T> requires std::is_floating_point_v<T>
	Biquad<T>LowPass( T Fc, T Q, T Fs );

	// calculate coefficients for a LowPass with 12dbOct Butterworth decay filter.
	template <typename T> requires std::is_floating_point_v<T>
	Biquad<T>LowPass12dbOct( T Fc, T Fs );

	// calculate coefficients for a 1stOrder LowPass filter.
	template <typename T> requires std::is_floating_point_v<T>
	Biquad<T>LowPass1stOrder( T Fc, T Fs );

	// calculate coefficients for a LowShelf filter.
	template <typename T> requires std::is_floating_point_v<T>
	Biquad<T>LowShelf( T peakGain, T Fc, T Fs );

	// calculate coefficients for a 1stOrder LowShelffilter.
	template <typename T> requires std::is_floating_point_v<T>
	Biquad<T>LowShelf1stOrder( T peakGain, T Fc, T Fs );

	// calculate coefficients for a LowShelf filter with Q factor.
	template <typename T> requires std::is_floating_point_v<T>
	Biquad<T>LowShelfQ( T peakGain, T Fc, T Q, T Fs );

	// calculate coefficients for a Notch filter with Q factor.
	template <typename T> requires std::is_floating_point_v<T>
	Biquad<T>Notch( T Fc, T Q, T Fs );

	// calculate coefficients for a OnePoleHighPass filter.
	template <typename T> requires std::is_floating_point_v<T>
	Biquad<T>OnePoleHighPass( T Fc, T Fs );

	// calculate coefficients for a OnePoleLowPass filter.
	template <typename T> requires std::is_floating_point_v<T>
	Biquad<T>OnePoleLowPass( T Fc, T Fs );

	// calculate coefficients for a Peaking EQ filter with Q factor.
	template <typename T> requires std::is_floating_point_v<T>
	Biquad<T>PeakEq( T peakGain, T Fc, T Q, T Fs );

	// calculate the  q factors for ButterworthResponce filter
	template <typename T> requires std::is_floating_point_v<T>
	std::vector< T > ButterworthResponceQfactors( int order );

	// calculate coefficients chain for cascade LowPass filters
	// with Butterworth response.
	template <typename T> requires std::is_floating_point_v<T>
	std::vector< Biquad<T> > LowPassCascadeAsButterworth( int order, T Fc, T Fs );

	// calculate coefficients chain for cascade HighPass filters
	// with Butterworth response.
	template <typename T> requires std::is_floating_point_v<T>
	std::vector< Biquad<T> > HighPassCascadeAsButterworth( int order, T Fc, T Fs );
}

#include "IIRDesignimpl.h"


