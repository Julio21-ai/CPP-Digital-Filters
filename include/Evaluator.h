#pragma once

#include <type_traits>
#include <complex>
#include <cmath>
#include <span>
#include "Constants.h"
#include "Biquad.h"
#include "FrequencyResponse.h"


namespace DigitalFilters::Eval
{
	// Evaluates the frequency response of a bi-quadratic filter in linear units
	// using trigonometric functions.
	// Assumes the Bi-quad struct has numerator coefficients (zeros) b0, a1, a2
	// and denominator coefficients (poles) b0, b1, b2 where b0 is typically 1.
	template <typename T>
		requires std::is_floating_point_v<T>
	FrequencyResponse<T> CalcFreqResponseTrig( Biquad<T> bicuad, T omega )
	{
		const T cos_omega = std::cos( -omega );
		const T cos_2omega = std::cos( T( 2.0 ) * -omega );
		const T sin_omega = std::sin( -omega );
		const T sin_2omega = std::sin( T( 2.0 ) * -omega );

		T realZeros =
			bicuad.a0 + (bicuad.a1 * cos_omega) + (bicuad.a2 * cos_2omega);

		T imagZeros =
			(bicuad.a1 * sin_omega) + (bicuad.a2 * sin_2omega);

		T realPoles =
			T( bicuad.b0 ) + (bicuad.b1 * cos_omega) + (bicuad.b2 * cos_2omega);

		T imagPoles =
			(bicuad.b1 * sin_omega) + (bicuad.b2 * sin_2omega);

		T divider = realPoles * realPoles + imagPoles * imagPoles;

		T realHw = (realZeros * realPoles + imagZeros * imagPoles) / divider;
		T imagHw = (imagZeros * realPoles - realZeros * imagPoles) / divider;

		return FrequencyResponse
		(

			std::sqrt( realHw * realHw + imagHw * imagHw ),
			std::atan2( imagHw, realHw )
		);

	};

	// Evaluates the frequency response of a bi-quadratic filter
	// in the complex domain.
	// Assumes the Bi-quad struct has numerator coefficients (zeros) b0, a1, a2
	// and denominator coefficients (poles) b0, b1, b2 where b0 is typically 1.
	template <typename T>
		requires std::is_floating_point_v<T>
	std::complex<T> CalcFreqResponse( Biquad<T> bicuad, T w )
	{
		std::complex<T> z_minus_1 = std::exp( std::complex<T>( 0.0, -1 * w ) );

		std::complex<T> z_minus_2 = std::exp( std::complex<T>( 0.0, -2 * w ) );

		std::complex<T> numerator =
			bicuad.a0 + bicuad.a1 * z_minus_1 + bicuad.a2 * z_minus_2;

		std::complex<T> denominator =
			bicuad.b0 + bicuad.b1 * z_minus_1 + bicuad.b2 * z_minus_2;

		// Handle potential division by zero
		// (though unlikely with normalized filters)
		if (std::abs( denominator ) < std::numeric_limits<T>::epsilon())
		{
			return
				std::complex<T>(
					std::numeric_limits<T>::infinity(),
					std::numeric_limits<T>::infinity()
				);
		}

		return numerator / denominator;

	};

	// Helper function to calculate the sum of complex exponentials
	// weighted by coefficients.
	template <typename T>
		requires std::is_floating_point_v<T>
	std::pair<T, T> CalculateComplexSum( std::span<const T> coefficients, T omega )
	{
		T realSum = 0.0;
		T imagSum = 0.0;

		for (size_t i = 0; i < coefficients.size(); ++i)
		{
			realSum += coefficients[i] * std::cos( static_cast<T>( i ) * -omega );
			imagSum += coefficients[i] * std::sin( static_cast<T>( i ) * -omega );
		}
		return { realSum, imagSum };
	}

	// Evaluates the frequency response of a general FIR/IIR filter
	// using trigonometric functions.
	// Assumes poles have a leading coefficient of
	template <typename T>
		requires std::is_floating_point_v<T>
	FrequencyResponse<T> CalcFreqResponseTrig(
		std::span<const T> numeratorCoeffs,
		std::span<const T> denominatorCoeffs,
		T omega )
	{
		auto [realNumerator, imagNumerator] =
			CalculateComplexSum( numeratorCoeffs, omega );

		auto [realDenominator, imagDenominator] =
			CalculateComplexSum( denominatorCoeffs, omega );

		T divider = realDenominator * realDenominator
			+ imagDenominator * imagDenominator;

		// Handle potential division by zero
		if (std::abs( divider ) < std::numeric_limits<T>::epsilon())
		{
			return FrequencyResponse<T>
			(
				std::numeric_limits<T>::infinity(),
				0.0
			);
		}

		T realHw = (realNumerator * realDenominator
							+ imagNumerator * imagDenominator)
							/ divider;

		T imagHw = (imagNumerator * realDenominator
							- realNumerator * imagDenominator)
							/ divider;

		return FrequencyResponse<T>
		(
			std::sqrt( realHw * realHw + imagHw * imagHw ),
			std::atan2( imagHw, realHw )
		);


	}


	// Function to evaluate Bi-quad filter
	template <typename T>	requires std::is_floating_point_v<T>
	std::complex<T> EvalCoeffsBiquad( std::span<const T> coeffs, T omega )
	{

		std::complex<T> result = static_cast<T>(0.0);
		std::complex<T> j_omega = std::complex<T>( 0.0, -omega );
		std::complex<T> z_power = static_cast<T>(1.0); // z^0

		for (std::size_t i = 0; i < coeffs.size(); ++i)
		{
			result += coeffs[i] * z_power;
			z_power *= std::exp( j_omega ); // z^(-i) where i is the loop index
		}
		return result;

	};

	// Evaluates the frequency response of a general FIR/IIR filter in the complex domain.
	// Assumes the first coefficient of the denominator is 1.
	template <typename T>
		requires std::is_floating_point_v<T>
	std::complex<T> CalcFreqResponse(
		std::span<const T> numeratorCoeffs,
		std::span<const T> denominatorCoeffs,
		T omega )
	{

		std::complex<T> numeratorResponse =
			EvalCoeffsBiquad( numeratorCoeffs, omega );
		std::complex<T> denominatorResponse =
			EvalCoeffsBiquad( denominatorCoeffs, omega );

		// Handle potential division by zero
		if (std::abs( denominatorResponse ) < std::numeric_limits<T>::epsilon())
		{
			return std::complex<T>
				(
					std::numeric_limits<T>::infinity(),
					std::numeric_limits<T>::infinity()
				);
		}

		return numeratorResponse / denominatorResponse;

	};


}

