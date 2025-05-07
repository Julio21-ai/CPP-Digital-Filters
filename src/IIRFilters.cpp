#include <math.h>
#include "BicuadCoefficients.h"
#include "DigitalFiltersConstants.h"
#include "IIRFilters.h"
#include <omp.h>
#include "FilterUtils.h"

using namespace DigitalFilters;

#pragma region HighShelf1stOrder
BicuadCoefficients IIRFilters::HighShelf1stOrder( double peakGain
	, double Fc, double Fs )
{
	const double gain = FilterUtils<double>::DecibelToLinearGain(peakGain );
	const double omega = FilterUtils<double>::PrewarpFrequency(Fc, Fs);
	double norm;

	double a0, a1, a2;
	double b1, b2;

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
	return BicuadCoefficients(a0,a1,a2,b1,b2);
}
#pragma endregion

#pragma region LowShelf1stOrder
BicuadCoefficients IIRFilters::LowShelf1stOrder( double peakGain
	, double Fc, double Fs )
{
	double gain =  FilterUtils<double>::DecibelToLinearGain(peakGain );
	double omega = FilterUtils<double>::PrewarpFrequency(Fc, Fs);
	double norm;

	double a0, a1, a2;
	double b1, b2;

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

	return 	BicuadCoefficients( a0, a1, a2, b1, b2 );
}
#pragma endregion

#pragma region HighPass1stOrder
BicuadCoefficients IIRFilters::HighPass1stOrder( double Fc, double Fs )
{
	double omega = FilterUtils<double>::PrewarpFrequency(Fc, Fs);
	double norm;

	double a0, a1, a2;
	double b1, b2;

	norm = 1 / (omega + 1);
	a0 = norm;
	a1 = -norm;
	b1 = (omega - 1) * norm;
	a2 = b2 = 0;

	return 	BicuadCoefficients( a0, a1, a2, b1, b2 );
}
#pragma endregion

#pragma region LowPass1stOrder
BicuadCoefficients IIRFilters::LowPass1stOrder( double Fc, double Fs )
{
	double omega = FilterUtils<double>::PrewarpFrequency(Fc, Fs);
	double norm;

	double a0, a1, a2;
	double b1, b2;

	norm = 1 / (1 / omega + 1);
	a0 = a1 = norm;
	b1 = (1 - 1 / omega) * norm;
	a2 = b2 = 0;

	return 	BicuadCoefficients( a0, a1, a2, b1, b2 );
}
#pragma endregion

#pragma region AllPass
BicuadCoefficients IIRFilters::AllPass1stOrder( double Fc, double Fs )
{

	double omega = FilterUtils<double>::PrewarpFrequency(Fc, Fs);
	double a0, a1, a2;
	double b1, b2;

	a0 = (1 - omega) / (1 + omega);
	a1 = -1;
	a2 = 0;
	b1 = -a0;
	b2 = 0;
	return 	BicuadCoefficients( a0, a1, a2, b1, b2 );
}
#pragma endregion

#pragma region AllPassQ
BicuadCoefficients IIRFilters::AllPassQ( double Fc, double Q,
	double Fs )
{
	double omega = FilterUtils<double>::PrewarpFrequency(Fc, Fs);
	double norm;

	double a0, a1, a2;
	double b1, b2;

	norm = 1 / (1 + omega / Q + omega * omega);
	a0 = (1 - omega / Q + omega * omega) * norm;
	a1 = 2 * (omega * omega - 1) * norm;
	a2 = 1;
	b1 = a1;
	b2 = a0;
	return 	BicuadCoefficients( a0, a1, a2, b1, b2 );
}
#pragma endregion

#pragma region OnePoleLowPass()
BicuadCoefficients IIRFilters::OnePoleLowPass( double Fc
	, double Fs
)
{
	double a0, a1, a2;
	double b1, b2;

	b1 = exp( -2.0 * double( MathConstants::pi ) * (Fc / Fs) );
	a0 = 1.0 - b1;
	b1 = -b1;
	a1 = a2 = b2 = 0;
	return 	BicuadCoefficients( a0, a1, a2, b1, b2 );
}
#pragma endregion

#pragma region OnePoleHighPass()
BicuadCoefficients IIRFilters::OnePoleHighPass( double Fc
	, double Fs
)
{
	double a0, a1, a2;
	double b1, b2;

	b1 = -exp( -2.0 * double( MathConstants::pi ) * (0.5 - Fc / Fs) ); //dubious -exp
	a0 = 1.0 + b1;
	b1 = -b1;
	a1 = a2 = b2 = 0;
	return 	BicuadCoefficients( a0, a1, a2, b1, b2 );
}

#pragma endregion

#pragma region LowPass
BicuadCoefficients IIRFilters::LowPass( double Fc, double Q, double Fs )
{
	double a0, a1, a2;
	double b1, b2;

	double omega = FilterUtils<double>::PrewarpFrequency(Fc, Fs);
	double norm;

	norm = 1 / (1 + omega / Q + omega * omega);
	a0 = omega * omega * norm;
	a1 = 2 * a0;
	a2 = a0;
	b1 = 2 * (omega * omega - 1) * norm;
	b2 = (1 - omega / Q + omega * omega) * norm;
	return 	BicuadCoefficients( a0, a1, a2, b1, b2 );
}
#pragma endregion

#pragma region LowPass12dbOct
BicuadCoefficients IIRFilters::LowPass12dbOct( double Fc
	, double Fs
)
{
	double a0, a1, a2;
	double b1, b2;

	double omega = FilterUtils<double>::PrewarpFrequency(Fc, Fs);
	double norm;
	//M_SQRT1_2
	norm = 1 / (1 + omega / double( MathConstants::m_1_Sqrt2 ) + omega * omega);
	a0 = omega * omega * norm;
	a1 = 2 * a0;
	a2 = a0;
	b1 = 2 * (omega * omega - 1) * norm;
	b2 = (1 - omega / double( MathConstants::m_1_Sqrt2 ) + omega * omega) * norm;
	return 	BicuadCoefficients( a0, a1, a2, b1, b2 );
}
#pragma endregion

#pragma region HighPass
BicuadCoefficients IIRFilters::HighPass( double Fc
	, double Q
	, double Fs
)
{
	double a0, a1, a2;
	double b1, b2;
	double norm;

	double omega = FilterUtils<double>::PrewarpFrequency(Fc, Fs);

	norm = 1 / (1 + omega / Q + omega * omega);
	a0 = 1 * norm;
	a1 = -2 * a0;
	a2 = a0;
	b1 = 2 * (omega * omega - 1) * norm;
	b2 = (1 - omega / Q + omega * omega) * norm;
	return 	BicuadCoefficients( a0, a1, a2, b1, b2 );
}
#pragma endregion

#pragma region HighPass12dbOct
BicuadCoefficients IIRFilters::HighPass12dbOct( double Fc, double Fs )
{
	double a0, a1, a2;
	double b1, b2;

	double norm;
	double omega = FilterUtils<double>::PrewarpFrequency(Fc, Fs);

	norm = 1 / (1 + omega / double( MathConstants::m_1_Sqrt2 ) + omega * omega);
	a0 = 1 * norm;
	a1 = -2 * a0;
	a2 = a0;
	b1 = 2 * (omega * omega - 1) * norm;
	b2 = (1 - omega / double( MathConstants::m_1_Sqrt2 ) + omega * omega) * norm;
	return 	BicuadCoefficients( a0, a1, a2, b1, b2 );
}

#pragma endregion

#pragma region BandPass
BicuadCoefficients IIRFilters::BandPass( double Fc
	, double Q
	, double Fs
)
{
	double a0, a1, a2;
	double b1, b2;

	double omega = FilterUtils<double>::PrewarpFrequency(Fc, Fs);
	double norm;
	norm = 1 / (1 + omega / Q + omega * omega);
	a0 = omega / Q * norm;
	a1 = 0;
	a2 = -a0;
	b1 = 2 * (omega * omega - 1) * norm;
	b2 = (1 - omega / Q + omega * omega) * norm;
	return 	BicuadCoefficients( a0, a1, a2, b1, b2 );

}
#pragma endregion

#pragma region Notch
BicuadCoefficients IIRFilters::Notch( double Fc
	, double Q
	, double Fs
)
{
	double a0, a1, a2;
	double b1, b2;

	double norm;
	double omega = FilterUtils<double>::PrewarpFrequency(Fc, Fs);
	norm = 1 / (1 + omega / Q + omega * omega);
	a0 = (1 + omega * omega) * norm;
	a1 = 2 * (omega * omega - 1) * norm;
	a2 = a0;
	b1 = a1;
	b2 = (1 - omega / Q + omega * omega) * norm;
	return 	BicuadCoefficients( a0, a1, a2, b1, b2 );
}
#pragma endregion

#pragma region PeakEq
BicuadCoefficients IIRFilters::PeakEq( double peakGain
	, double Fc
	, double Q
	, double Fs
)
{
	double a0, a1, a2;
	double b1, b2;

	double norm;
	double gain = FilterUtils<double>::DecibelToLinearGain(peakGain );
	double omega = FilterUtils<double>::PrewarpFrequency(Fc, Fs);
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

	return 	BicuadCoefficients( a0, a1, a2, b1, b2 );

}
#pragma endregion

#pragma region HighShelf
BicuadCoefficients IIRFilters::HighShelf( double peakGain
	, double Fc
	, double Fs )
{

	double a0, a1, a2;
	double b1, b2;

	double norm;
	double gain = FilterUtils<double>::DecibelToLinearGain(peakGain );
	double omega = FilterUtils<double>::PrewarpFrequency(Fc, Fs);

	if (peakGain >= 0)
	{
		norm = 1 / (1 + double( MathConstants::sqrt2 ) * omega + omega * omega);
		a0 = (gain + sqrt( 2 * gain ) * omega + omega * omega) * norm;
		a1 = 2 * (omega * omega - gain) * norm;
		a2 = (gain - sqrt( 2 * gain ) * omega + omega * omega) * norm;
		b1 = 2 * (omega * omega - 1) * norm;
		b2 = (1 - double( MathConstants::sqrt2 ) * omega + omega * omega) * norm;
	}
	else
	{
		norm = 1 / (gain + sqrt( 2 * gain ) * omega + omega * omega);
		a0 = (1 + double( MathConstants::sqrt2 ) * omega + omega * omega) * norm;
		a1 = 2 * (omega * omega - 1) * norm;
		a2 = (1 - double( MathConstants::sqrt2 ) * omega + omega * omega) * norm;
		b1 = 2 * (omega * omega - gain) * norm;
		b2 = (gain - sqrt( 2 * gain ) * omega + omega * omega) * norm;
	}
	return 	BicuadCoefficients( a0, a1, a2, b1, b2 );
}
#pragma endregion

#pragma region HighShelfQ
BicuadCoefficients IIRFilters::HighShelfQ( double peakGain
	, double Fc
	, double Q
	, double Fs )
{
	double a0, a1, a2;
	double b1, b2;

	double norm;
	double gain = FilterUtils<double>::DecibelToLinearGain(peakGain );
	double omega = FilterUtils<double>::PrewarpFrequency(Fc, Fs);

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
	return 	BicuadCoefficients( a0, a1, a2, b1, b2 );
}
#pragma endregion

#pragma region LowShelf
BicuadCoefficients IIRFilters::LowShelf( double peakGain
	, double Fc
	, double Fs
)
{
	double a0, a1, a2;
	double b1, b2;

	double norm;
	double gain = FilterUtils<double>::DecibelToLinearGain(peakGain );
	double omega = FilterUtils<double>::PrewarpFrequency(Fc, Fs);

	if (peakGain >= 0)
	{
		norm = 1 / (1 + double( MathConstants::sqrt2 ) * omega + omega * omega);
		a0 = (1 + sqrt( 2 * gain ) * omega + gain * omega * omega) * norm;
		a1 = 2 * (gain * omega * omega - 1) * norm;
		a2 = (1 - sqrt( 2 * gain ) * omega + gain * omega * omega) * norm;
		b1 = 2 * (omega * omega - 1) * norm;
		b2 = (1 - double( MathConstants::sqrt2 ) * omega + omega * omega) * norm;
	}
	else
	{
		norm = 1 / (1 + sqrt( 2 * gain ) * omega + gain * omega * omega);
		a0 = (1 + double( MathConstants::sqrt2 ) * omega + omega * omega) * norm;
		a1 = 2 * (omega * omega - 1) * norm;
		a2 = (1 - double( MathConstants::sqrt2 ) * omega + omega * omega) * norm;
		b1 = 2 * (gain * omega * omega - 1) * norm;
		b2 = (1 - sqrt( 2 * gain ) * omega + gain * omega * omega) * norm;
	}

	return 	BicuadCoefficients( a0, a1, a2, b1, b2 );

}
#pragma endregion

#pragma region LowShelfQ
BicuadCoefficients IIRFilters::LowShelfQ( double peakGain
	, double Fc
	, double Q
	, double Fs
)
{
	double a0, a1, a2;
	double b1, b2;

	double norm;
	double gain = FilterUtils<double>::DecibelToLinearGain(peakGain );
	double omega = FilterUtils<double>::PrewarpFrequency(Fc, Fs);

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

	return 	BicuadCoefficients( a0, a1, a2, b1, b2 );

}
#pragma endregion

#pragma region ButterworthResponceQfactors()
std::vector<double> IIRFilters::ButterworthResponceQfactors( int fiterOrder )
{
	int pairs = fiterOrder >> 1;
	int oddPoles = fiterOrder & 1;
	double poleInc = double( DigitalFilters::MathConstants::pi ) / fiterOrder;

	std::vector<double> qVals;
	double firstAngle = poleInc;

	if (!oddPoles)
	{
		firstAngle /= 2;
	}
	else
	{
		qVals.push_back( 0.5 );
	}

	for (int idx = 0; idx < pairs; idx++)
	{
		double qVal = 1.0 / (2.0 * cos( firstAngle + idx * poleInc ));
		qVals.push_back( qVal );
	}

	return qVals;

}

#pragma endregion

#pragma region LowPassCascadeAsButterworth()
std::vector<BicuadCoefficients> IIRFilters::LowPassCascadeAsButterworth(
	int order, double Fc, double Fs )
{
	std::vector<BicuadCoefficients> coefficients;

	std::vector<double> qfactors =
		IIRFilters::ButterworthResponceQfactors( order );

	for (std::vector<double>::iterator iter; iter != qfactors.end(); iter++)
	{
		coefficients.push_back( LowPass( Fc, *iter, Fs ) );
	}

	return std::vector<BicuadCoefficients>();
}
#pragma endregion

#pragma region HighPassCascadeAsButterworth()
std::vector<BicuadCoefficients> IIRFilters::HighPassCascadeAsButterworth(
	int order, double Fc, double Fs )
{
	std::vector<BicuadCoefficients> coefficients;

	std::vector<double> qfactors =
		IIRFilters::ButterworthResponceQfactors( order );

	for (std::vector<double>::iterator iter; iter != qfactors.end(); iter++)
	{
		coefficients.push_back( HighPass( Fc, *iter, Fs ) );
	}

	return std::vector<BicuadCoefficients>();
}
#pragma endregion

