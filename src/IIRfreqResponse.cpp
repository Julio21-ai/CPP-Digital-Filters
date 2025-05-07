#include "IIRfreqResponse.h"
#include "FilterEvaluator.h"
#include <omp.h>
#include <FilterUtils.h>


using namespace DigitalFilters;

#pragma region std::complex<double> EvalBicuad( BicuadCoefficients... )
std::complex<double> IIRfreqResponse::EvalBicuad(
	const BicuadCoefficients& coef, double fc, double fs)
{
	double w = FilterUtils<double>::HzToW(fc) / fs;
	return	FilterEvaluator<double>::EvalBicuad(
		coef.getA0(), coef.getA1(), coef.getA2(),
		coef.getB1(), coef.getB2(), w);
}
#pragma endregion

#pragma region std::complex<double> EvalBicuad(double...)
std::complex<double> DigitalFilters::IIRfreqResponse::EvalBicuad(double a0
	, double a1, double a2, double b1, double b2, double fc, double fs)
{
	double w = FilterUtils<double>::HzToW(fc) / fs;
	return	FilterEvaluator<double>::EvalBicuad(a0, a1, a2, b1, b2, w);
}
#pragma endregion

#pragma region std::complex<double> FrequencyResponse(const std::vector<double>&...)
std::complex<double> DigitalFilters::IIRfreqResponse::FrequencyResponse(
	const std::vector<double>& zeros, const std::vector<double>& poles,
	double fc, double fs)
{
	double w = FilterUtils<double>::HzToW(fc) / fs;

	int filterOrder = static_cast<int>(std::min(poles.size(), zeros.size()));

	return FilterEvaluator<double>::FrequencyResponse(
		zeros.data(), poles.data(), filterOrder, w);
}
#pragma endregion

#pragma region std::vector<std::complex<double>> FrequencyResponse(const std::vector<double>&...)

std::vector<std::complex<double>> IIRfreqResponse::FrequencyResponse(
	const std::vector<double>& zeros,
	const std::vector<double>& poles,
	const std::vector<double>& freqs,
	double fs)
{
	int filterOrder = static_cast<int>(std::min(poles.size(), zeros.size()));

	std::vector<std::complex<double>> result(freqs.size());

#pragma omp parallel for
	for(int i = 0; i < (int)freqs.size(); ++i)
	{
		double w = FilterUtils<double>::HzToW(freqs[i]) / fs;
		result[i] = FilterEvaluator<double>::FrequencyResponse(
			zeros.data(), poles.data(), filterOrder, w);
	}

	return result;

}
#pragma endregion

#pragma region std::pair<double, double> EvalBicuadTrig(const BicuadCoefficients&...)
std::pair<double, double> DigitalFilters::IIRfreqResponse::EvalBicuadTrig(
	const BicuadCoefficients& coef, double fc, double fs)
{
	double w = FilterUtils<double>::HzToW(fc) / fs;

	return	FilterEvaluator<double>::
		EvalBicuadTrig(coef.getA0(), coef.getA1(), coef.getA2(),
		coef.getB1(), coef.getB2(), w);
}

#pragma endregion

#pragma region std::pair<double, double> EvalBicuadTrig(double a0...)
std::pair<double, double> DigitalFilters::IIRfreqResponse::EvalBicuadTrig(double a0
	, double a1, double a2, double b1, double b2, double fc, double fs)
{
	double w = FilterUtils<double>::HzToW(fc) / fs;
	return	FilterEvaluator<double>::EvalBicuadTrig(a0, a1, a2, b1, b2, w);
}
#pragma endregion

#pragma region std::pair<double, double> FrequencyResponseTrig(const std::vector<double>&...)
std::pair<double, double>
DigitalFilters::IIRfreqResponse::FrequencyResponseTrig(
	const std::vector<double>& poles, const std::vector<double>& zeros,
	double fc, double fs)
{
	double w = FilterUtils<double>::HzToW(fc) / fs;

	int filterOrder = static_cast<int>(std::min(poles.size(), zeros.size()));
	return FilterEvaluator<double>::FrequencyResponseTrig(
		zeros.data(), poles.data(), filterOrder, w);
}
#pragma endregion

#pragma region std::vector<std::pair<double, double>> FrequencyResponseTrig(const std::vector<double>&...)
std::vector<std::pair<double, double>> IIRfreqResponse::FrequencyResponseTrig(
	const std::vector<double>& zeros,
	const std::vector<double>& poles,
	const std::vector<double>& freqs,
	double fs)
{
	int filterOrder = static_cast<int>(std::min(poles.size(), zeros.size()));

	std::vector<std::pair<double, double> > result(freqs.size());

#pragma omp parallel for
	for(int i = 0; i < (int)freqs.size(); ++i)
	{
		double w = FilterUtils<double>::HzToW(freqs[i]) / fs;
		result[i] = FilterEvaluator<double>::FrequencyResponseTrig(
			zeros.data(), poles.data(), filterOrder, w);
	}

	return result;
}

#pragma endregion

#pragma region GainTodB()
double DigitalFilters::IIRfreqResponse::GainTodB(double g)
{
	return FilterUtils<double>::GainTodB(g);
}

#pragma endregion

#pragma region HzToW()
double DigitalFilters::IIRfreqResponse::HzToW(double hz)
{
	return FilterUtils<double>::HzToW(hz);
}

#pragma endregion
