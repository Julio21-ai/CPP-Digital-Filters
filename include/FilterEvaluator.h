#pragma once
#ifndef FILTER_EVALUATOR_H
#define FILTER_EVALUATOR_H

#include <type_traits>
#include <complex>
#include "DigitalFiltersConstants.h"


namespace DigitalFilters
{
	// This class assumes Zeros (Numerator) to be A coefficients
	// and Poles (Denominator) to be B coefficients
	// Bi-quad filters have b0 = 1 constant.

	template <typename T,
		typename = std::enable_if_t<std::is_floating_point_v<T>>>
	class  FilterEvaluator
	{
	public:

		#pragma region EvalBicuadTrig()

		// Function to evaluate Bi-quad filter response in linear units
		//  using trigonometric functions
		static std::pair<T, T> EvalBicuadTrig( T a0, T a1, T a2, T b1, T b2, T w )
		{
			T cos_w = std::cos( -w );
			T sin_w = std::sin( -w );

			T cos_2w = std::cos( static_cast <T>(2.0) * -w );
			T sin_2w = std::sin( static_cast <T>(2.0) * -w );

			T realZeros = a0 + (a1 * cos_w) + (a2 * cos_2w);
			T imagZeros = (a1 * sin_w) + (a2 * sin_2w);

			T realPoles = T( 1.0 ) + (b1 * cos_w) + (b2 * cos_2w);
			T imagPoles = (b1 * sin_w) + (b2 * sin_2w);

			T divider = realPoles * realPoles + imagPoles * imagPoles;
			T realHw = (realZeros * realPoles + imagZeros * imagPoles) / divider;
			T imagHw = (imagZeros * realPoles - realZeros * imagPoles) / divider;

			T magnitude = std::sqrt( realHw * realHw + imagHw * imagHw );
			T phase = std::atan2( imagHw, realHw );

			return std::pair<T, T>( magnitude, phase );
		};
#pragma endregion

		#pragma region EvalBicuad()

		// Function to evaluate Bi-quad filter response in linear
		//  using complex functions
		static std::complex<T> EvalBicuad( T a0, T a1, T a2, T b1, T b2, T w )
		{
			std::complex<T> complex_exp =
				std::exp( std::complex<T>( 0.0, -w ) );

			std::complex<T> complex_exp_2 =
				std::exp( std::complex<T>( 0.0, static_cast <T>(2.0) * -w ) );

			std::complex<T> numerator = a0 + a1 * complex_exp + a2 * complex_exp_2;
			std::complex<T> denominator =
				static_cast<T>(1.0)
				+ b1 * complex_exp
				+ b2 * complex_exp_2;

			return numerator / denominator;
		};
#pragma endregion

		#pragma region FrequencyResponseTrig()

		// Function to evaluate filter response in linear units
		// using trigonometric functions
		// poles and zeros must have the same length with poles b0 = 1
		static std::pair<T, T>  FrequencyResponseTrig( const T* zeros, const T* poles,
			int filterOrder, T w )
		{
			T realZeros = 0.0;
			T imagZeros = 0.0;
			T realPoles = 0.0;
			T imagPoles = 0.0;

			for (int i = 0; i < filterOrder; i++)
			{
				T cosI = cos( w * static_cast <T>( i ) );
				T sinI = sin( w * static_cast <T>( i ) );
				realZeros += zeros[i] * cosI;
				imagZeros += zeros[i] * sinI;
				realPoles += poles[i] * cosI;
				imagPoles += poles[i] * sinI;
			}

			T divider = realPoles * realPoles + imagPoles * imagPoles;
			T realHw = (realZeros * realPoles + imagZeros * imagPoles) / divider;
			T imagHw = (imagZeros * realPoles - realZeros * imagPoles) / divider;
			T magnitude = sqrt( realHw * realHw + imagHw * imagHw );
			T phase = atan2( -imagHw, realHw );

			return std::pair<T, T>( magnitude, phase );
		};
#pragma endregion

		#pragma region FrequencyResponse()

		// Function to evaluate filter response in linear units 
		// using complex functions 
		// poles and zeros must have the same length with poles b0 = 1
		static std::complex<T> FrequencyResponse( const T* zeros, const T* poles,
			int filterOrder, T w )
		{
			std::complex<T> resZeros;
			std::complex<T> resPoles;
			std::complex<T> complex_exp = exp( std::complex<T>( 0.0, w ) );

			for (int i = 0; i < filterOrder; i++)
			{
				std::complex<T>
					complex_exp_i = std::pow( complex_exp, static_cast <T>( -i ) );

				resZeros += zeros[i] * complex_exp_i;
				resPoles += poles[i] * complex_exp_i;
			}
			return (resZeros / resPoles);
		};

#pragma endregion




	};

}

#endif // FILTER_EVALUATOR_H