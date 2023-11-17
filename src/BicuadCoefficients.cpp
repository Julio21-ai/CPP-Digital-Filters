#include <math.h>
#include "BicuadCoefficients.h"
#include "DigitalFiltersConstants.h"

/*==============================================================================
**
** Calculate Coefficients for the filters
**
*/
using namespace DigitalFilters;

#pragma region GetPoles()
std::vector<double> BicuadCoefficients::GetPoles()
{
	std::vector<double> retval;

	retval.push_back(this->a0);
	retval.push_back(this->a1);
	retval.push_back(this->a2);

	return retval;
}
#pragma endregion

#pragma region GetZeros()
std::vector<double> BicuadCoefficients::GetZeros()
{
	std::vector<double> retval;

	retval.push_back(this->b0);
	retval.push_back(this->b1);
	retval.push_back(this->b2);

	return retval;
}
#pragma endregion

#pragma region HighShelf1stOrder
BicuadCoefficients BicuadCoefficients::HighShelf1stOrder(double peakGain
	, double Fc, double Fs)
{
	BicuadCoefficients coef;
	double V = pow(10, fabs(peakGain) / 20);
	double K = tan(double(MathConstants::pi) * Fc / Fs);
	double norm;

	if(peakGain >= 0)
	{
		norm = 1 / (K + 1);
		coef.a0 = (K + V) * norm;
		coef.a1 = (K - V) * norm;
		coef.a2 = 0;
		coef.b1 = (K - 1) * norm;
		coef.b2 = 0;
	}
	else
	{
		norm = 1 / (K + V);
		coef.a0 = (K + 1) * norm;
		coef.a1 = (K - 1) * norm;
		coef.a2 = 0;
		coef.b1 = (K - V) * norm;
		coef.b2 = 0;
	}
	return coef;
}
#pragma endregion

#pragma region LowShelf1stOrder
BicuadCoefficients BicuadCoefficients::LowShelf1stOrder(double peakGain
	, double Fc, double Fs)
{
	BicuadCoefficients coef;
	double V = pow(10, fabs(peakGain) / 20);
	double K = tan(double(MathConstants::pi) * Fc / Fs);
	double norm;

	if(peakGain >= 0)
	{
		norm = 1 / (K + 1);
		coef.a0 = (K * V + 1) * norm;
		coef.a1 = (K * V - 1) * norm;
		coef.a2 = 0;
		coef.b1 = (K - 1) * norm;
		coef.b2 = 0;
	}
	else
	{
		norm = 1 / (K * V + 1);
		coef.a0 = (K + 1) * norm;
		coef.a1 = (K - 1) * norm;
		coef.a2 = 0;
		coef.b1 = (K * V - 1) * norm;
		coef.b2 = 0;
	}

	return coef;
}
#pragma endregion

#pragma region HighPass1stOrder
BicuadCoefficients BicuadCoefficients::HighPass1stOrder(double Fc, double Fs)
{
	BicuadCoefficients coef;
	double K = tan(double(MathConstants::pi) * Fc / Fs);
	double norm;

	norm = 1 / (K + 1);
	coef.a0 = norm;
	coef.a1 = -norm;
	coef.b1 = (K - 1) * norm;
	coef.a2 = coef.b2 = 0;

	return coef;
}
#pragma endregion

#pragma region LowPass1stOrder
BicuadCoefficients BicuadCoefficients::LowPass1stOrder( double Fc, double Fs)
{
	BicuadCoefficients coef;
	double K = tan(double(MathConstants::pi) * Fc / Fs);
	double norm;

	norm = 1 / (1 / K + 1);
	coef.a0 = coef.a1 = norm;
	coef.b1 = (1 - 1 / K) * norm;
	coef.a2 = coef.b2 = 0;

	return coef;
}
#pragma endregion

#pragma region AllPass
BicuadCoefficients BicuadCoefficients::AllPass1stOrder( double Fc, double Fs)
{
	BicuadCoefficients coef;

	double K = tan(double(MathConstants::pi) * Fc / Fs);

	coef.a0 = (1 - K) / (1 + K);
	coef.a1 = -1;
	coef.a2 = 0;
	coef.b1 = -coef.a0;
	coef.b2 = 0;
	return coef;
}
#pragma endregion

#pragma region AllPassQ
BicuadCoefficients BicuadCoefficients::AllPassQ(double Fc, double Q,
	double Fs)
{
	BicuadCoefficients coef;

	double K = tan(double(MathConstants::pi) * Fc / Fs);
	double norm;

	norm = 1 / (1 + K / Q + K * K);
	coef.a0 = (1 - K / Q + K * K) * norm;
	coef.a1 = 2 * (K * K - 1) * norm;
	coef.a2 = 1;
	coef.b1 = coef.a1;
	coef.b2 = coef.a0;
	return coef;
}
#pragma endregion

#pragma region OnePoleLowPass()
BicuadCoefficients BicuadCoefficients::OnePoleLowPass(double Fc
	, double Fs
)
{
	BicuadCoefficients coef;

	coef.b1 = exp(-2.0 * double(MathConstants::pi) * (Fc / Fs));
	coef.a0 = 1.0 - coef.b1;
	coef.b1 = -coef.b1;
	coef.a1 = coef.a2 = coef.b2 = 0;
	return coef;
}
#pragma endregion

#pragma region OnePoleHighPass()
BicuadCoefficients BicuadCoefficients::OnePoleHighPass(double Fc
	, double Fs
)
{
	BicuadCoefficients coef;

	coef.b1 = -exp(-2.0 * double(MathConstants::pi) * (0.5 - Fc / Fs)); //dubious -exp
	coef.a0 = 1.0 + coef.b1;
	coef.b1 = -coef.b1;
	coef.a1 = coef.a2 = coef.b2 = 0;
	return coef;
}

#pragma endregion

#pragma region LowPass
BicuadCoefficients BicuadCoefficients::LowPass(double Fc
	, double Q
	, double Fs
)
{
	BicuadCoefficients coef;

	double K = tan(double(MathConstants::pi) * Fc / Fs);
	double norm;

	norm = 1 / (1 + K / Q + K * K);
	coef.a0 = K * K * norm;
	coef.a1 = 2 * coef.a0;
	coef.a2 = coef.a0;
	coef.b1 = 2 * (K * K - 1) * norm;
	coef.b2 = (1 - K / Q + K * K) * norm;
	return coef;
}
#pragma endregion

#pragma region HighPass
BicuadCoefficients BicuadCoefficients::HighPass( double Fc
	, double Q
	, double Fs
)
{
	BicuadCoefficients coef;
	double norm;

	double K = tan(double(MathConstants::pi) * Fc / Fs);

	norm = 1 / (1 + K / Q + K * K);
	coef.a0 = 1 * norm;
	coef.a1 = -2 * coef.a0;
	coef.a2 = coef.a0;
	coef.b1 = 2 * (K * K - 1) * norm;
	coef.b2 = (1 - K / Q + K * K) * norm;
	return coef;
}
#pragma endregion

#pragma region BandPass
BicuadCoefficients BicuadCoefficients::BandPass(double Fc
	, double Q
	, double Fs
)
{
	BicuadCoefficients coef;
	double K = tan(double(MathConstants::pi) * Fc / Fs);
	double norm;
	norm = 1 / (1 + K / Q + K * K);
	coef.a0 = K / Q * norm;
	coef.a1 = 0;
	coef.a2 = -coef.a0;
	coef.b1 = 2 * (K * K - 1) * norm;
	coef.b2 = (1 - K / Q + K * K) * norm;
	return coef;

}
#pragma endregion

#pragma region Notch
BicuadCoefficients BicuadCoefficients::Notch(double Fc
	, double Q
	, double Fs
)
{
	BicuadCoefficients coef;
	double norm;
	double K = tan(double(MathConstants::pi) * Fc / Fs);
	norm = 1 / (1 + K / Q + K * K);
	coef.a0 = (1 + K * K) * norm;
	coef.a1 = 2 * (K * K - 1) * norm;
	coef.a2 = coef.a0;
	coef.b1 = coef.a1;
	coef.b2 = (1 - K / Q + K * K) * norm;
	return coef;
}
#pragma endregion

#pragma region PeakEq
BicuadCoefficients BicuadCoefficients::PeakEq(double peakGain
	, double Fc
	, double Q
	, double Fs
)
{
	BicuadCoefficients coef;
	double norm;
	double V = pow(10, fabs(peakGain) / 20);
	double K = tan(double(MathConstants::pi) * Fc / Fs);
	if(peakGain >= 0)
	{
		norm = 1 / (1 + 1 / Q * K + K * K);
		coef.a0 = (1 + V / Q * K + K * K) * norm;
		coef.a1 = 2 * (K * K - 1) * norm;
		coef.a2 = (1 - V / Q * K + K * K) * norm;
		coef.b1 = coef.a1;
		coef.b2 = (1 - 1 / Q * K + K * K) * norm;
	}
	else
	{
		norm = 1 / (1 + V / Q * K + K * K);
		coef.a0 = (1 + 1 / Q * K + K * K) * norm;
		coef.a1 = 2 * (K * K - 1) * norm;
		coef.a2 = (1 - 1 / Q * K + K * K) * norm;
		coef.b1 = coef.a1;
		coef.b2 = (1 - V / Q * K + K * K) * norm;
	}

	return coef;

}
#pragma endregion

#pragma region HighShelf
BicuadCoefficients BicuadCoefficients::HighShelf(double peakGain
	, double Fc
	, double Fs)
{

	BicuadCoefficients coef;
	double norm;
	double V = pow(10, fabs(peakGain) / 20);
	double K = tan( double(MathConstants::pi) * Fc / Fs);
	if(peakGain >= 0)
	{
		norm = 1 / (1 + double(MathConstants::sqrt2) * K + K * K);
		coef.a0 = (V + sqrt(2 * V) * K + K * K) * norm;
		coef.a1 = 2 * (K * K - V) * norm;
		coef.a2 = (V - sqrt(2 * V) * K + K * K) * norm;
		coef.b1 = 2 * (K * K - 1) * norm;
		coef.b2 = (1 - double(MathConstants::sqrt2)  * K + K * K) * norm;
	}
	else
	{
		norm = 1 / (V + sqrt(2 * V) * K + K * K);
		coef.a0 = (1 + double(MathConstants::sqrt2)  * K + K * K) * norm;
		coef.a1 = 2 * (K * K - 1) * norm;
		coef.a2 = (1 - double(MathConstants::sqrt2)  * K + K * K) * norm;
		coef.b1 = 2 * (K * K - V) * norm;
		coef.b2 = (V - sqrt(2 * V) * K + K * K) * norm;
	}
	return coef;
}
#pragma endregion

#pragma region HighShelfQ
BicuadCoefficients BicuadCoefficients::HighShelfQ(double peakGain
	, double Fc
	, double Q
	, double Fs)
{
	BicuadCoefficients coef;
	double norm;
	double V = pow(10, fabs(peakGain) / 20);
	double K = tan( double(MathConstants::pi) * Fc / Fs);

	if(peakGain >= 0)
	{
		norm = 1 / (1 + 1 / Q * K + K * K);
		coef.a0 = (V + sqrt(2 * V) * K + K * K) * norm;
		coef.a1 = 2 * (K * K - V) * norm;
		coef.a2 = (V - sqrt(2 * V) * K + K * K) * norm;
		coef.b1 = 2 * (K * K - 1) * norm;
		coef.b2 = (1 - 1 / Q * K + K * K) * norm;
	}
	else
	{
		norm = 1 / (V + sqrt(2 * V) * K + K * K);
		coef.a0 = (1 + 1 / Q * K + K * K) * norm;
		coef.a1 = 2 * (K * K - 1) * norm;
		coef.a2 = (1 - 1 / Q * K + K * K) * norm;
		coef.b1 = 2 * (K * K - V) * norm;
		coef.b2 = (V - sqrt(2 * V) * K + K * K) * norm;
	}
	return coef;
}
#pragma endregion

#pragma region LowShelf
BicuadCoefficients BicuadCoefficients::LowShelf(double peakGain
	, double Fc
	, double Fs
)
{
	BicuadCoefficients coef;
	double norm;
	double V = pow(10, fabs(peakGain) / 20);
	double K = tan(double(MathConstants::pi) * Fc / Fs);

	if(peakGain >= 0)
	{
		norm = 1 / (1 + double(MathConstants::sqrt2)  * K + K * K);
		coef.a0 = (1 + sqrt(2 * V) * K + V * K * K) * norm;
		coef.a1 = 2 * (V * K * K - 1) * norm;
		coef.a2 = (1 - sqrt(2 * V) * K + V * K * K) * norm;
		coef.b1 = 2 * (K * K - 1) * norm;
		coef.b2 = (1 - double(MathConstants::sqrt2)  * K + K * K) * norm;
	}
	else
	{
		norm = 1 / (1 + sqrt(2 * V) * K + V * K * K);
		coef.a0 = (1 + double(MathConstants::sqrt2)  * K + K * K) * norm;
		coef.a1 = 2 * (K * K - 1) * norm;
		coef.a2 = (1 - double(MathConstants::sqrt2)  * K + K * K) * norm;
		coef.b1 = 2 * (V * K * K - 1) * norm;
		coef.b2 = (1 - sqrt(2 * V) * K + V * K * K) * norm;
	}


	return coef;

}
#pragma endregion

#pragma region LowShelfQ
BicuadCoefficients BicuadCoefficients::LowShelfQ(double peakGain
	, double Fc
	, double Q
	, double Fs
)
{
	BicuadCoefficients coef;
	double norm;
	double V = pow(10, fabs(peakGain) / 20);
	double K = tan(double(MathConstants::pi) * Fc / Fs);

	if(peakGain >= 0)
	{    // boost
		norm = 1 / (1 + 1 / Q * K + K * K);
		coef.a0 = (1 + sqrt(V) / Q * K + V * K * K) * norm;
		coef.a1 = 2 * (V * K * K - 1) * norm;
		coef.a2 = (1 - sqrt(V) / Q * K + V * K * K) * norm;
		coef.b1 = 2 * (K * K - 1) * norm;
		coef.b2 = (1 - 1 / Q * K + K * K) * norm;
	}
	else
	{    // cut
		norm = 1 / (1 + sqrt(V) / Q * K + V * K * K);
		coef.a0 = (1 + 1 / Q * K + K * K) * norm;
		coef.a1 = 2 * (K * K - 1) * norm;
		coef.a2 = (1 - 1 / Q * K + K * K) * norm;
		coef.b1 = 2 * (V * K * K - 1) * norm;
		coef.b2 = (1 - sqrt(V) / Q * K + V * K * K) * norm;
	}

	return coef;

}
#pragma endregion

