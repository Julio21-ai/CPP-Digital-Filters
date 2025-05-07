#pragma once

#ifndef IIR_FILTERS_H
#define IIR_FILTERS_H

#ifndef DIGITALFILTERS_STATIC_LIB
#if defined(DIGITALFILTERS_EXPORTS)
#define DIGITALFILTERS_MODULE_LIB __declspec(dllexport)
#else
#define DIGITALFILTERS_MODULE_LIB __declspec(dllimport)
#endif
#else
#define DIGITALFILTERS_MODULE_LIB
#endif


#include "BicuadCoefficients.h"

namespace DigitalFilters
{
	// Class representing coefficients for a bi-quadratic filter
	// Functions Parameters:
	//   - peakGain: Peak gain of the filter in Db.
	//   - Fc: Center frequency of the filter in Hz.
	//   - Q: Quality factor of the filter.
	//   - Fs: Sampling frequency in Hz.

	class DIGITALFILTERS_MODULE_LIB IIRFilters
	{
		public:
		#pragma region Filter Coefficients Calc
		// calculate coefficients for a 1stOrder AllPass filter.
		static BicuadCoefficients AllPass1stOrder	(
			double Fc,
			double Fs );

		// calculate coefficients for a AllPass filter with Q factor.
		static BicuadCoefficients AllPassQ(
			double Fc,
			double Q,
			double Fs );

		// calculate coefficients for a BandPass filter.
		static BicuadCoefficients BandPass(
			double Fc,
			double Q,
			double Fs );

		// calculate coefficients for a HighPass filter.
		static BicuadCoefficients HighPass(
			double Fc,
			double Q,
			double Fs );

		// calculate coefficients for a HighPass filter.
		static BicuadCoefficients HighPass12dbOct(
			double Fc,
			double Fs );

		// calculate coefficients for a 1stOrder HighPass1stOrder filter.
		static BicuadCoefficients HighPass1stOrder(
			double Fc,
			double Fs );

		// calculate coefficients chain for cascade HighPass filters with Butterworth response.
		static std::vector<BicuadCoefficients> HighPassCascadeAsButterworth(
			int order,
			double Fc,
			double Fs );

		// calculate coefficients for a HighPass filter.
		static BicuadCoefficients HighShelf(
			double peakGain,
			double Fc,
			double Fs );

		// calculate coefficients for a 1stOrder HighShelf filter.
		static BicuadCoefficients HighShelf1stOrder(
			double peakGain,
			double Fc,
			double Fs );

		// calculate coefficients for a HighPass filter with Q factor.
		static BicuadCoefficients HighShelfQ(
			double peakGain,
			double Fc,
			double Q,
			double Fs );

		// calculate coefficients for a LowPass filter.
		static BicuadCoefficients LowPass(
			double Fc,
			double Q,
			double Fs );

		// calculate coefficients for a LowPass with 12dbOct Butterworth decay filter.
		static BicuadCoefficients LowPass12dbOct(
			double Fc,
			double Fs );

		// calculate coefficients for a 1stOrder LowPass filter.
		static BicuadCoefficients LowPass1stOrder(
			double Fc,
			double Fs );

		// calculate coefficients chain for cascade LowPass filters with Butterworth response.
		static std::vector<BicuadCoefficients> LowPassCascadeAsButterworth(
			int order,
			double Fc,
			double Fs );

		// calculate coefficients for a LowShelf filter.
		static BicuadCoefficients LowShelf(
			double peakGain,
			double Fc,
			double Fs );

		// calculate coefficients for a 1stOrder LowShelffilter.
		static BicuadCoefficients LowShelf1stOrder(
			double peakGain,
			double Fc,
			double Fs );

		// calculate coefficients for a LowShelf filter with Q factor.
		static BicuadCoefficients LowShelfQ(
			double peakGain,
			double Fc,
			double Q,
			double Fs );

		// calculate coefficients for a Notch filter with Q factor.
		static BicuadCoefficients Notch(
			double Fc,
			double Q,
			double Fs );

		// calculate coefficients for a OnePoleHighPass filter.
		static BicuadCoefficients OnePoleHighPass(
			double Fc,
			double Fs );

		// calculate coefficients for a OnePoleLowPass filter.
		static BicuadCoefficients OnePoleLowPass(
			double Fc,
			double Fs );

		// calculate coefficients for a Peaking EQ filter with Q factor.
		static BicuadCoefficients PeakEq(
			double peakGain,
			double Fc,
			double Q,
			double Fs );

		// calculate the  q factors for ButterworthResponce filter
		static std::vector<double> ButterworthResponceQfactors(
			int order );

#pragma endregion


	};

}

#endif