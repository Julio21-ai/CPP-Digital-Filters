#include "IIRfreqResponse.h"
#include "Evaluator.h"
#include <omp.h>
#include <span>
#include <Utils.h>


using namespace DigitalFilters;
using namespace DigitalFilters::Utils;
using namespace DigitalFilters::Eval;

#pragma region std::complex<double> EvalBicuad( BiquadCoefficientsDouble... )
std::complex<double> IIRfreqResponse::EvalBicuad(
	const BiquadCoefficientsDouble& coef, double fc, double fs )
{
	double w = HzToOmega( fc ) / fs;
	return	Eval::CalcFreqResponse(coef, w );
}
#pragma endregion

#pragma region std::complex<double> EvalBicuad(double...)
std::complex<double> DigitalFilters::IIRfreqResponse::EvalBicuad( double a0
	, double a1, double a2, double b1, double b2, double fc, double fs )
{
	double w = HzToOmega( fc ) / fs;
	return	Eval::CalcFreqResponse(
		BiquadCoefficientsDouble(a0, a1, a2, b1, b2), w );
}
#pragma endregion

#pragma region std::complex<double> FrequencyResponse(const std::vector<double>&...)
std::complex<double> DigitalFilters::IIRfreqResponse::FrequencyResponse(
	const std::vector<double>& zeros, const std::vector<double>& poles,
	double fc, double fs )
{
	double w = HzToOmega( fc ) / fs;
	std::span mySpan1( zeros );
	std::span mySpan2( poles );

	return Eval::CalcFreqResponse(
		mySpan1,
		mySpan2,
		w);
}
#pragma endregion

#pragma region std::vector<std::complex<double>> FrequencyResponse(const std::vector<double>&...)

std::vector<std::complex<double>> IIRfreqResponse::FrequencyResponse(
	const std::vector<double>& zeros,
	const std::vector<double>& poles,
	const std::vector<double>& freqs,
	double fs )
{

	std::vector<std::complex<double>> result( freqs.size() );
	std::span mySpan1( zeros );
	std::span mySpan2( poles );

	#pragma omp parallel for
	for (int i = 0; i < (int)freqs.size(); ++i)
	{
		double w = HzToOmega( freqs[i] ) / fs;
		result[i] = Eval::CalcFreqResponse( mySpan1, mySpan2, w );
	}

	return result;

}
#pragma endregion

#pragma region FrequencyResponseDouble EvalBicuadTrig(const BiquadCoefficientsDouble&...)
FrequencyResponseDouble DigitalFilters::IIRfreqResponse::EvalBicuadTrig(
	const BiquadCoefficientsDouble& coef, double fc, double fs )
{
	double w = HzToOmega( fc ) / fs;

	return	Eval::CalcFreqResponseTrig( coef, w );
}

#pragma endregion

#pragma region std::pair<double, double> EvalBicuadTrig(double a0...)
FrequencyResponseDouble  DigitalFilters::IIRfreqResponse::EvalBicuadTrig( double a0
	, double a1, double a2, double b1, double b2, double fc, double fs )
{
	double w = HzToOmega( fc ) / fs;
	return	Eval::CalcFreqResponseTrig(
		BiquadCoefficientsDouble(a0, a1, a2, b1, b2), w );
}
#pragma endregion

#pragma region std::pair<double, double> FrequencyResponseTrig(const std::vector<double>&...)
FrequencyResponseDouble
DigitalFilters::IIRfreqResponse::FrequencyResponseTrig(
	const std::vector<double>& poles, const std::vector<double>& zeros,
	double fc, double fs )
{
	double w = HzToOmega( fc ) / fs;

	std::span z ( zeros );

	std::span p ( poles );
	return Eval::CalcFreqResponseTrig<double>(
		zeros, poles, w );
}
#pragma endregion

#pragma region std::vector<std::pair<double, double>> FrequencyResponseTrig(const std::vector<double>&...)
std::vector<FrequencyResponseDouble > IIRfreqResponse::FrequencyResponseTrig(
	const std::vector<double>& zeros,
	const std::vector<double>& poles,
	const std::vector<double>& freqs,
	double fs )
{

	std::vector<FrequencyResponseDouble > result( freqs.size() );

#pragma omp parallel for
	for (int i = 0; i < (int)freqs.size(); ++i)
	{
		double w = HzToOmega( freqs[i] ) / fs;
		result[i] = Eval::CalcFreqResponseTrig<double>(zeros, poles, w );
	}

	return result;
}

#pragma endregion


