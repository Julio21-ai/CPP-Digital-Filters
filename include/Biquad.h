#pragma once
#include <type_traits>
#include <vector>
#include <complex>
#include <stdexcept>

namespace DigitalFilters
{
	// Represents the coefficients for a second-order (bi-quadratic)
	// digital filter.
	//
	// The transfer function in the Z-domain is typically represented as:
	//
	//        Y(z)   a0 + a1*z^-1 + a2*z^-2
	// H(z) = ---- = ---------------------
	//        X(z)   b0 + b1*z^-1 + b2*z^-2
	//
	// Where:
	//
	// - a0, a1, a2 are the feed-forward (numerator)
	// coefficients (often associated with "zeros").
	//
	// - b0, b1, b2 are the feedback (denominator)
	// coefficients (often associated with "poles").

	template <typename T>
		requires std::is_floating_point_v<T>
	struct Biquad
	{
		// Feed-forward coefficients (Numerator, often related to Zeros)
		T a0 = 0, a1 = 0, a2 = 0;

		// Feedback coefficients (Denominator, often related to Poles)
		T b0 = 1, b1 = 0, b2 = 0;

		Biquad () = default;

		// Constructor with full parameters
		Biquad ( T a0, T a1, T a2, T b0, T b1, T b2 )
			: a0( a0 ), a1( a1 ), a2( a2 ), b0( b0 ), b1( b1 ), b2( b2 )
		{
			// It's common practice to normalize b0 to 1 to simplify calculations
			if (b0 != static_cast<T>(0))
			{
				T normalizationFactor = b0;
				this->a0 /= normalizationFactor;
				this->a1 /= normalizationFactor;
				this->a2 /= normalizationFactor;
				this->b0 /= normalizationFactor;
				this->b1 /= normalizationFactor;
				this->b2 /= normalizationFactor;
			}
			else
			{
				throw std::invalid_argument(
					"The denominator coefficient b0 cannot be zero." );
			}
		}

		// Constructor with b0 = 1 implicit
		Biquad ( T a0, T a1, T a2, T b1, T b2 )
			: a0( a0 ), a1( a1 ), a2( a2 ),
			b0( static_cast<T>(1) ), b1( b1 ), b2( b2 )
		{
		}

		// Returns the feed-forward coefficients ( numerator ).
		std::vector <T> GetNumeratorCoefficients() const
		{
			return { a0, a1, a2 };
		}

		// Returns the feedback coefficients (denominator).
		std::vector <T> GetDenominatorCoefficients() const
		{
			return{ b0, b1, b2 };
		}

		// Calculates the poles of the transfer function.
		std::vector<std::complex<T>> calculatePoles() const
		{

			std::vector<std::complex<T>> poles;
			if (std::abs( b2 ) < std::numeric_limits<T>::epsilon())
			{
				// First-order case (b2 is approximately zero)
				if (std::abs( b1 ) > std::numeric_limits<T>::epsilon())
				{
					poles.emplace_back( -b0 / b1, static_cast<T>(0) );
				}
				// If both b1 and b2 are zero,
				//	there are no finite poles (only at infinity)
			}
			else
			{
				T discriminant = b1 * b1 - 4 * b0 * b2;

				if (discriminant >= 0)
				{
					poles.emplace_back
					(
						(-b1 + std::sqrt( discriminant )) / (2 * b2), static_cast<T>(0)
					);
					poles.emplace_back
					(
						(-b1 - std::sqrt( discriminant )) / (2 * b2), static_cast<T>(0)
					);
				}
				else
				{
					poles.emplace_back
					(
						-b1 / (2 * b2), std::sqrt( -discriminant ) / (2 * b2)
					);
					poles.emplace_back
					(
						-b1 / (2 * b2), -std::sqrt( -discriminant ) / (2 * b2)
					);
				}

			}

			return poles;
		}

		// Calculates the zeros of the transfer function.
		std::vector<std::complex<T>> calculateZeros() const
		{
			std::vector<std::complex<T>> zeros;
			if (std::abs( a2 ) < std::numeric_limits<T>::epsilon())
			{
				// First-order case (a2 is approximately zero)
				if (std::abs( a1 ) > std::numeric_limits<T>::epsilon())
				{
					zeros.emplace_back( -a0 / a1, static_cast<T>(0) );
				}
				// If both a1 and a2 are zero, there are no finite zeros
				//	(only at infinity if a0 is non-zero)
				else if (std::abs( a0 ) > std::numeric_limits<T>::epsilon())
				{
					// A zero at z = 0 if a0 is zero and a1 or a2 are not.
				}
			}
			else
			{
				T discriminant = a1 * a1 - 4 * a0 * a2;
				if (discriminant >= 0)
				{
					zeros.emplace_back
					(
						(-a1 + std::sqrt( discriminant )) / (2 * a2), static_cast<T>(0)
					);
					zeros.emplace_back
					(
						(-a1 - std::sqrt( discriminant )) / (2 * a2), static_cast<T>(0)
					);
				}
				else
				{
					zeros.emplace_back
					(
						-a1 / (2 * a2), std::sqrt( -discriminant ) / (2 * a2)
					);

					zeros.emplace_back
					(
						-a1 / (2 * a2), -std::sqrt( -discriminant ) / (2 * a2)
					);
				}
			}
			return zeros;


		};


	};
}

