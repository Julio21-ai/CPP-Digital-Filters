#pragma once

#include <math.h>
#include "Biquad.h"
#include "Constants.h"
#include "Utils.h"

namespace DigitalFilters::IIR
{
	using namespace Utils;
	using namespace Constants;
	using std::vector;

	template <typename T> requires std::is_floating_point_v<T>
	Biquad<T> HighShelf1stOrder( T peakGain, T Fc, T Fs )
	{
		const T gain = DecibelToLinearGain( peakGain );
		const T omega = PrewarpFrequency( Fc, Fs );
		T norm;

		T a0, a1, a2;
		T b1, b2;

		if (peakGain >= 0)
		{
			norm = 1 / (omega + 1);
			a0 = (omega + gain) * norm;
			a1 = (omega - gain) * norm;
			a2 = 0;
			b1 = (omega - 1) * norm;
			b2 = 0;
		}
		else
		{
			norm = 1 / (omega + gain);
			a0 = (omega + 1) * norm;
			a1 = (omega - 1) * norm;
			a2 = 0;
			b1 = (omega - gain) * norm;
			b2 = 0;
		}
		return 	Biquad<T>( a0, a1, a2, b1, b2 );
	}

	template <typename T> requires std::is_floating_point_v<T>
	Biquad<T> LowShelf1stOrder( T peakGain, T Fc, T Fs )
	{
		T gain = DecibelToLinearGain( peakGain );
		T omega = PrewarpFrequency( Fc, Fs );
		T norm;

		T a0, a1, a2;
		T b1, b2;

		if (peakGain >= 0)
		{
			norm = 1 / (omega + 1);
			a0 = (omega * gain + 1) * norm;
			a1 = (omega * gain - 1) * norm;
			a2 = 0;
			b1 = (omega - 1) * norm;
			b2 = 0;
		}
		else
		{
			norm = 1 / (omega * gain + 1);
			a0 = (omega + 1) * norm;
			a1 = (omega - 1) * norm;
			a2 = 0;
			b1 = (omega * gain - 1) * norm;
			b2 = 0;
		}

		return 	Biquad<T>( a0, a1, a2, b1, b2 );
	}

	template <typename T> requires std::is_floating_point_v<T>
	Biquad<T> HighPass1stOrder( T Fc, T Fs )
	{
		T omega = PrewarpFrequency( Fc, Fs );
		T norm;

		T a0, a1, a2;
		T b1, b2;

		norm = 1 / (omega + 1);
		a0 = norm;
		a1 = -norm;
		b1 = (omega - 1) * norm;
		a2 = b2 = 0;

		return 	Biquad<T>( a0, a1, a2, b1, b2 );
	}

	template <typename T> requires std::is_floating_point_v<T>
	Biquad<T> LowPass1stOrder( T Fc, T Fs )
	{
		T omega = PrewarpFrequency( Fc, Fs );
		T norm;

		T a0, a1, a2;
		T b1, b2;

		norm = 1 / (1 / omega + 1);
		a0 = a1 = norm;
		b1 = (1 - 1 / omega) * norm;
		a2 = b2 = 0;

		return 	Biquad<T>( a0, a1, a2, b1, b2 );
	}

	template <typename T> requires std::is_floating_point_v<T>
	Biquad<T> AllPass1stOrder( T Fc, T Fs )
	{

		T omega = PrewarpFrequency( Fc, Fs );
		T a0, a1, a2;
		T b1, b2;

		a0 = (1 - omega) / (1 + omega);
		a1 = -1;
		a2 = 0;
		b1 = -a0;
		b2 = 0;
		return 	Biquad<T>( a0, a1, a2, b1, b2 );
	}

	template <typename T> requires std::is_floating_point_v<T>
	Biquad<T> AllPassQ( T Fc, T Q, T Fs )
	{
		T omega = PrewarpFrequency( Fc, Fs );
		T norm;

		T a0, a1, a2;
		T b1, b2;

		norm = 1 / (1 + omega / Q + omega * omega);
		a0 = (1 - omega / Q + omega * omega) * norm;
		a1 = 2 * (omega * omega - 1) * norm;
		a2 = 1;
		b1 = a1;
		b2 = a0;
		return 	Biquad<T>( a0, a1, a2, b1, b2 );
	}

	template <typename T> requires std::is_floating_point_v<T>
	Biquad<T> OnePoleLowPass( T Fc, T Fs )
	{
		T a0, a1, a2;
		T b1, b2;

		b1 = exp( -2.0 * pi<T>() * (Fc / Fs) );
		a0 = 1.0 - b1;
		b1 = -b1;
		a1 = a2 = b2 = 0;
		return 	Biquad<T>( a0, a1, a2, b1, b2 );
	}

	template <typename T> requires std::is_floating_point_v<T>
	Biquad<T> OnePoleHighPass( T Fc, T Fs )
	{
		T a0, a1, a2;
		T b1, b2;

		b1 = -exp( -2.0 * pi<T>() * (0.5 - Fc / Fs) ); //dubious -exp
		a0 = 1.0 + b1;
		b1 = -b1;
		a1 = a2 = b2 = 0;
		return 	Biquad<T>( a0, a1, a2, b1, b2 );
	}

	template <typename T> requires std::is_floating_point_v<T>
	Biquad<T> LowPass( T Fc, T Q, T Fs )
	{
		T a0, a1, a2;
		T b1, b2;

		T omega = PrewarpFrequency( Fc, Fs );
		T norm;

		norm = 1 / (1 + omega / Q + omega * omega);
		a0 = omega * omega * norm;
		a1 = 2 * a0;
		a2 = a0;
		b1 = 2 * (omega * omega - 1) * norm;
		b2 = (1 - omega / Q + omega * omega) * norm;
		return 	Biquad<T>( a0, a1, a2, b1, b2 );
	}

	template <typename T> requires std::is_floating_point_v<T>
	Biquad<T> LowPass12dbOct( T Fc, T Fs )
	{
		T a0, a1, a2;
		T b1, b2;

		T omega = PrewarpFrequency( Fc, Fs );
		T norm;
		norm = 1 / (1 + omega / one_over_sqrt2<T>() + omega * omega);
		a0 = omega * omega * norm;
		a1 = 2 * a0;
		a2 = a0;
		b1 = 2 * (omega * omega - 1) * norm;
		b2 = (1 - omega / one_over_sqrt2<T>() + omega * omega) * norm;
		return 	Biquad<T>( a0, a1, a2, b1, b2 );
	}

	template <typename T> requires std::is_floating_point_v<T>
	Biquad<T> HighPass( T Fc, T Q, T Fs )
	{
		T a0, a1, a2;
		T b1, b2;
		T norm;

		T omega = PrewarpFrequency( Fc, Fs );

		norm = 1 / (1 + omega / Q + omega * omega);
		a0 = 1 * norm;
		a1 = -2 * a0;
		a2 = a0;
		b1 = 2 * (omega * omega - 1) * norm;
		b2 = (1 - omega / Q + omega * omega) * norm;
		return 	Biquad<T>( a0, a1, a2, b1, b2 );
	}

	template <typename T> requires std::is_floating_point_v<T>
	Biquad<T> HighPass12dbOct( T Fc, T Fs )
	{
		T a0, a1, a2;
		T b1, b2;

		T norm;
		T omega = PrewarpFrequency( Fc, Fs );

		norm = 1 / (1 + omega / one_over_sqrt2<T>() + omega * omega);
		a0 = 1 * norm;
		a1 = -2 * a0;
		a2 = a0;
		b1 = 2 * (omega * omega - 1) * norm;
		b2 = (1 - omega / one_over_sqrt2<T>() + omega * omega) * norm;
		return 	Biquad<T>( a0, a1, a2, b1, b2 );
	}

	template <typename T> requires std::is_floating_point_v<T>
	Biquad<T> BandPass( T Fc, T Q, T Fs )
	{
		T a0, a1, a2;
		T b1, b2;

		T omega = PrewarpFrequency( Fc, Fs );
		T norm;
		norm = 1 / (1 + omega / Q + omega * omega);
		a0 = omega / Q * norm;
		a1 = 0;
		a2 = -a0;
		b1 = 2 * (omega * omega - 1) * norm;
		b2 = (1 - omega / Q + omega * omega) * norm;
		return 	Biquad<T>( a0, a1, a2, b1, b2 );

	}

	template <typename T> requires std::is_floating_point_v<T>
	Biquad<T> Notch( T Fc, T Q, T Fs )
	{
		T a0, a1, a2;
		T b1, b2;

		T norm;
		T omega = PrewarpFrequency( Fc, Fs );
		norm = 1 / (1 + omega / Q + omega * omega);
		a0 = (1 + omega * omega) * norm;
		a1 = 2 * (omega * omega - 1) * norm;
		a2 = a0;
		b1 = a1;
		b2 = (1 - omega / Q + omega * omega) * norm;
		return 	Biquad<T>( a0, a1, a2, b1, b2 );
	}

	template <typename T> requires std::is_floating_point_v<T>
	Biquad<T> PeakEq( T peakGain, T Fc, T Q, T Fs )
	{
		T a0, a1, a2;
		T b1, b2;

		T norm;
		T gain = DecibelToLinearGain( peakGain );
		T omega = PrewarpFrequency( Fc, Fs );
		if (peakGain >= 0)
		{
			norm = 1 / (1 + 1 / Q * omega + omega * omega);
			a0 = (1 + gain / Q * omega + omega * omega) * norm;
			a1 = 2 * (omega * omega - 1) * norm;
			a2 = (1 - gain / Q * omega + omega * omega) * norm;
			b1 = a1;
			b2 = (1 - 1 / Q * omega + omega * omega) * norm;
		}
		else
		{
			norm = 1 / (1 + gain / Q * omega + omega * omega);
			a0 = (1 + 1 / Q * omega + omega * omega) * norm;
			a1 = 2 * (omega * omega - 1) * norm;
			a2 = (1 - 1 / Q * omega + omega * omega) * norm;
			b1 = a1;
			b2 = (1 - gain / Q * omega + omega * omega) * norm;
		}

		return 	Biquad<T>( a0, a1, a2, b1, b2 );

	}

	template <typename T> requires std::is_floating_point_v<T>
	Biquad<T> HighShelf( T peakGain, T Fc, T Fs )
	{

		T a0, a1, a2;
		T b1, b2;

		T norm;
		T gain = DecibelToLinearGain( peakGain );
		T omega = PrewarpFrequency( Fc, Fs );

		if (peakGain >= 0)
		{
			norm = 1 / (1 + sqrt2 <T>() * omega + omega * omega);
			a0 = (gain + sqrt( 2 * gain ) * omega + omega * omega) * norm;
			a1 = 2 * (omega * omega - gain) * norm;
			a2 = (gain - sqrt( 2 * gain ) * omega + omega * omega) * norm;
			b1 = 2 * (omega * omega - 1) * norm;
			b2 = (1 - sqrt2<T>() * omega + omega * omega) * norm;
		}
		else
		{
			norm = 1 / (gain + sqrt( 2 * gain ) * omega + omega * omega);
			a0 = (1 + sqrt2<T>() * omega + omega * omega) * norm;
			a1 = 2 * (omega * omega - 1) * norm;
			a2 = (1 - sqrt2<T>() * omega + omega * omega) * norm;
			b1 = 2 * (omega * omega - gain) * norm;
			b2 = (gain - sqrt( 2 * gain ) * omega + omega * omega) * norm;
		}
		return 	Biquad<T>( a0, a1, a2, b1, b2 );
	}

	template <typename T> requires std::is_floating_point_v<T>
	Biquad<T> HighShelfQ( T peakGain, T Fc, T Q, T Fs )
	{
		T a0, a1, a2;
		T b1, b2;

		T norm;
		T gain = DecibelToLinearGain( peakGain );
		T omega = PrewarpFrequency( Fc, Fs );

		if (peakGain >= 0)
		{
			norm = 1 / (1 + 1 / Q * omega + omega * omega);
			a0 = (gain + sqrt( 2 * gain ) * omega + omega * omega) * norm;
			a1 = 2 * (omega * omega - gain) * norm;
			a2 = (gain - sqrt( 2 * gain ) * omega + omega * omega) * norm;
			b1 = 2 * (omega * omega - 1) * norm;
			b2 = (1 - 1 / Q * omega + omega * omega) * norm;
		}
		else
		{
			norm = 1 / (gain + sqrt( 2 * gain ) * omega + omega * omega);
			a0 = (1 + 1 / Q * omega + omega * omega) * norm;
			a1 = 2 * (omega * omega - 1) * norm;
			a2 = (1 - 1 / Q * omega + omega * omega) * norm;
			b1 = 2 * (omega * omega - gain) * norm;
			b2 = (gain - sqrt( 2 * gain ) * omega + omega * omega) * norm;
		}
		return 	Biquad<T>( a0, a1, a2, b1, b2 );
	}

	template <typename T> requires std::is_floating_point_v<T>
	Biquad<T> LowShelf( T peakGain, T Fc, T Fs )
	{
		T a0, a1, a2;
		T b1, b2;

		T norm;
		T gain = DecibelToLinearGain( peakGain );
		T omega = PrewarpFrequency( Fc, Fs );

		if (peakGain >= 0)
		{
			norm = 1 / (1 + sqrt2<T>() * omega + omega * omega);
			a0 = (1 + sqrt( 2 * gain ) * omega + gain * omega * omega) * norm;
			a1 = 2 * (gain * omega * omega - 1) * norm;
			a2 = (1 - sqrt( 2 * gain ) * omega + gain * omega * omega) * norm;
			b1 = 2 * (omega * omega - 1) * norm;
			b2 = (1 - sqrt2<T>() * omega + omega * omega) * norm;
		}
		else
		{
			norm = 1 / (1 + sqrt( 2 * gain ) * omega + gain * omega * omega);
			a0 = (1 + sqrt2<T>() * omega + omega * omega) * norm;
			a1 = 2 * (omega * omega - 1) * norm;
			a2 = (1 - sqrt2<T>() * omega + omega * omega) * norm;
			b1 = 2 * (gain * omega * omega - 1) * norm;
			b2 = (1 - sqrt( 2 * gain ) * omega + gain * omega * omega) * norm;
		}

		return 	Biquad<T>( a0, a1, a2, b1, b2 );

	}

	template <typename T> requires std::is_floating_point_v<T>
	Biquad<T> LowShelfQ( T peakGain, T Fc, T Q, T Fs )
	{
		T a0, a1, a2;
		T b1, b2;

		T norm;
		T gain = DecibelToLinearGain( peakGain );
		T omega = PrewarpFrequency( Fc, Fs );

		if (peakGain >= 0)
		{    // boost
			norm = 1 / (1 + 1 / Q * omega + omega * omega);
			a0 = (1 + sqrt( gain ) / Q * omega + gain * omega * omega) * norm;
			a1 = 2 * (gain * omega * omega - 1) * norm;
			a2 = (1 - sqrt( gain ) / Q * omega + gain * omega * omega) * norm;
			b1 = 2 * (omega * omega - 1) * norm;
			b2 = (1 - 1 / Q * omega + omega * omega) * norm;
		}
		else
		{    // cut
			norm = 1 / (1 + sqrt( gain ) / Q * omega + gain * omega * omega);
			a0 = (1 + 1 / Q * omega + omega * omega) * norm;
			a1 = 2 * (omega * omega - 1) * norm;
			a2 = (1 - 1 / Q * omega + omega * omega) * norm;
			b1 = 2 * (gain * omega * omega - 1) * norm;
			b2 = (1 - sqrt( gain ) / Q * omega + gain * omega * omega) * norm;
		}

		return 	Biquad<T>( a0, a1, a2, b1, b2 );

	}

	template <typename T> requires std::is_floating_point_v<T>
	vector< T > ButterworthResponceQfactors( int fiterOrder )
	{
		int pairs = fiterOrder >> 1;
		int oddPoles = fiterOrder & 1;
		T poleInc = pi<T>() / fiterOrder;

		vector<T> qVals;
		T firstAngle = poleInc;

		if (!oddPoles)
		{
			firstAngle /= 2;
		}
		else
		{
			qVals.push_back( static_cast<T>(0.5));
		}

		for (int idx = 0; idx < pairs; idx++)
		{
			T qVal = static_cast<T>( 1.0 ) /
				(static_cast<T>( 2.0 ) * cos( firstAngle + idx * poleInc ));
			qVals.push_back( qVal );
		}

		return qVals;
	}

	template <typename T> requires std::is_floating_point_v<T>
	vector<Biquad<T>> LowPassCascadeAsButterworth( int order, T Fc, T Fs )
	{
		vector<Biquad<T>> coefficients;

		vector<T> qfactors = ButterworthResponseQfactors<T>( order );

		for (auto iter = qfactors.begin(); iter != qfactors.end(); iter++)
		{
			coefficients.push_back( LowPass( Fc, *iter, Fs ) );
		}

		return coefficients;
	}

	template <typename T> requires std::is_floating_point_v<T>
	vector<Biquad<T>> HighPassCascadeAsButterworth( int order, T Fc, T Fs )
	{
		std::vector<Biquad<T>> coefficients;

		std::vector<T> qfactors =
			ButterworthResponceQfactors<T>( order );

		for (auto iter = qfactors.begin(); iter != qfactors.end(); iter++)
		{
			coefficients.push_back( HighPass( Fc, *iter, Fs ) );
		}

		return coefficients();
	}

}