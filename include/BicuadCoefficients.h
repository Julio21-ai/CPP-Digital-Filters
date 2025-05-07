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

	// Class representing coefficients for a bi-quadratic filter.
	// This class assumes Zeros (Numerator) to be A coefficients
	// and Poles (Denominator) to be B coefficients.
	// Bi-quad filters have b0 = 1 constant.
	// Functions Parameters:
	//   - peakGain: Peak gain of the filter in Db.
	//   - Fc: Center frequency of the filter in Hz.
	//   - Q: Quality factor of the filter.
	//   - Fs: Sampling frequency in Hz.

			// Represents coefficients for a bi quadratic filter
	class DIGITALFILTERS_MODULE_LIB BicuadCoefficients {
	private:
		// Numerator (zeros)
		double a0, a1, a2;
		// Denominator (poles)
		double b0, b1, b2;

	public:
		// Default constructor
		BicuadCoefficients() = default;

		// Constructor with full parameters
		BicuadCoefficients(
			double a0_Value,
			double a1_Value,
			double a2_Value,
			double b0_Value,
			double b1_Value,
			double b2_Value )
			: a0( a0_Value ),
			a1( a1_Value ),
			a2( a2_Value ),
			b0( b0_Value ),
			b1( b1_Value ),
			b2( b2_Value ) { }

		// Constructor with b0 = 1 implicit
		BicuadCoefficients(
			double a0_Value,
			double a1_Value,
			double a2_Value,
			double b1_Value,
			double b2_Value )
			: a0( a0_Value ),
			a1( a1_Value ),
			a2( a2_Value ),
			b0( 1.0 ),
			b1( b1_Value ),
			b2( b2_Value ) { }

		// Getters and setters
		double getA0() const { return a0; }
		void setA0( double value ) { a0 = value; }

		double getA1() const { return a1; }
		void setA1( double value ) { a1 = value; }

		double getA2() const { return a2; }
		void setA2( double value ) { a2 = value; }

		double getB0() const { return b0; }
		void setB0( double value ) { b0 = value; }

		double getB1() const { return b1; }
		void setB1( double value ) { b1 = value; }

		double getB2() const { return b2; }
		void setB2( double value ) { b2 = value; }

		// Returns [b0, b1, b2] (Poles)
		std::vector<double> GetPoles();
		// Returns [a0, a1, a2] (Zeros)
		std::vector<double> GetZeros();
	};

}

#endif // BICUAD_COEFFICIENTS_H
