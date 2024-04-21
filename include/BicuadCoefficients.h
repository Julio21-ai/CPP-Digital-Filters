#pragma once

#ifndef BICUAD_COEFFICIENTS_H
#define BICUAD_COEFFICIENTS_H

#ifndef DIGITALFILTERS_STATIC_LIB
#if defined(DIGITALFILTERS_EXPORTS)
#define DIGITALFILTERS_MODULE_LIB __declspec(dllexport)
#else
#define DIGITALFILTERS_MODULE_LIB __declspec(dllimport)
#endif
#else
#define DIGITALFILTERS_MODULE_LIB 
#endif


#include <vector>

namespace DigitalFilters
{

// Class representing coefficients for a biquadratic filter.
// This class assumes Zeros (Numerator) to be A coefficients 
// and Poles (Denominator) to be B coefficients.
// Biquad filters have b0 = 1 constant.
// Functions Parameters:
//   - peakGain: Peak gain of the filter in Db.
//   - Fc: Center frequency of the filter in Hz.
//   - Q: Quality factor of the filter.
//   - Fs: Sampling frequency in Hz.


// Class representing coefficients for a biquadratic filter.
class DIGITALFILTERS_MODULE_LIB BicuadCoefficients
{

#pragma region Fields
private:

	double a0, a1, a2; // numerator Zeros 
	double b0, b1, b2; // denominator Poles  

#pragma endregion

public:

#pragma region Constructors
	// Default constructor with zero-initialized coefficients.
	BicuadCoefficients(): a0(0), a1(0), a2(0), b0(1), b1(0), b2(0)
	{
	}

	// Constructor with parameters for initializing coefficients.
	explicit BicuadCoefficients(double a0_Value, double a1_Value, double a2_Value,
		double b0_Value, double b1_Value, double b2_Value)
		: a0(a0_Value), a1(a1_Value), a2(a2_Value),
		b0(b0_Value), b1(b1_Value), b2(b2_Value)
	{
	}
#pragma endregion

#pragma region properties
	// Properites for Zeros a0, a1, a2
	inline double getA0() const {
		return a0;
	}
	inline void setA0(double value)
	{
		a0 = value;
	}

	inline double getA1() const
	{
		return a1;
	}
	inline void setA1(double value)
	{
		a1 = value;
	}

	inline double getA2() const
	{
		return a2;
	}
	inline void setA2(double value)
	{
		a2 = value;
	}

	// Properites for poles b 1, b1, b2

	inline double getB0() const
	{
		return b0;
	}
	inline void setB0(double value)
	{
		b0 = value;
	}

	inline double getB1() const
	{
		return b1;
	}
	inline void setB1(double value)
	{
		b1 = value;
	}

	inline double getB2() const
	{
		return b2;
	}
	inline void setB2(double value)
	{
		b2 = value;
	}

	std::vector<double> GetPoles();
	std::vector<double> GetZeros();


#pragma endregion

#pragma region Filter Coefficients Calc
	// calculate coefficients for a 1stOrder AllPass filter.
	static BicuadCoefficients AllPass1stOrder	(
		double Fc,
		double Fs);

	// calculate coefficients for a AllPass filter with Q factor.
	static BicuadCoefficients AllPassQ(
		double Fc,
		double Q,
		double Fs);

	// calculate coefficients for a BandPass filter.
	static BicuadCoefficients BandPass(
		double Fc,
		double Q, 
		double Fs);

	// calculate coefficients for a HighPass filter.
	static BicuadCoefficients HighPass(
		double Fc,
		double Q,
		double Fs);

	// calculate coefficients for a HighPass filter.
	static BicuadCoefficients HighPass12dbOct(
		double Fc,
		double Fs);

	// calculate coefficients for a 1stOrder HighPass1stOrder filter.
	static BicuadCoefficients HighPass1stOrder(
		double Fc,
		double Fs);

	// calculate coefficients chain for cascade HighPass filters with Butterworth response.
	static std::vector<BicuadCoefficients> HighPassCascadeAsButterworth(
		int order,
		double Fc,
		double Fs);

	// calculate coefficients for a HighPass filter.
	static BicuadCoefficients HighShelf(
		double peakGain,
		double Fc, 
		double Fs);

	// calculate coefficients for a 1stOrder HighShelf filter.
	static BicuadCoefficients HighShelf1stOrder(
		double peakGain,
		double Fc,
		double Fs);

	// calculate coefficients for a HighPass filter with Q factor.
	static BicuadCoefficients HighShelfQ(
		double peakGain,
		double Fc,
		double Q,
		double Fs);

	// calculate coefficients for a LowPass filter.
	static BicuadCoefficients LowPass(
		double Fc,
		double Q,
		double Fs);

	// calculate coefficients for a LowPass with 12dbOct Butterworth decay filter.
	static BicuadCoefficients LowPass12dbOct(
		double Fc,
		double Fs);

	// calculate coefficients for a 1stOrder LowPass filter.
	static BicuadCoefficients LowPass1stOrder(
		double Fc,
		double Fs);

	// calculate coefficients chain for cascade LowPass filters with Butterworth response.
	static std::vector<BicuadCoefficients> LowPassCascadeAsButterworth(
		int order,
		double Fc,
		double Fs);

	// calculate coefficients for a LowShelf filter.
	static BicuadCoefficients LowShelf(
		double peakGain,
		double Fc,
		double Fs);

	// calculate coefficients for a 1stOrder LowShelffilter.
	static BicuadCoefficients LowShelf1stOrder(
		double peakGain,
		double Fc,
		double Fs);

	// calculate coefficients for a LowShelf filter with Q factor.
	static BicuadCoefficients LowShelfQ(
		double peakGain,
		double Fc,
		double Q,
		double Fs);

	// calculate coefficients for a Notch filter with Q factor.
	static BicuadCoefficients Notch(
		double Fc,
		double Q,
		double Fs);

	// calculate coefficients for a OnePoleHighPass filter.
	static BicuadCoefficients OnePoleHighPass(
		double Fc,
		double Fs);

	// calculate coefficients for a OnePoleLowPass filter.
	static BicuadCoefficients OnePoleLowPass(
		double Fc,
		double Fs);

	// calculate coefficients for a Peaking EQ filter with Q factor.
	static BicuadCoefficients PeakEq(
		double peakGain,
		double Fc, 
		double Q, 
		double Fs);

	// calculastes the  q factors for ButterworthResponce filter
	static std::vector<double> ButterworthResponceQfactors(
		int order);

#pragma endregion


};

}

#endif 