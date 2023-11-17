#pragma once
#include <complex>
#include <vector>
#include "BicuadCoefficients.h"
namespace DigitalFilters
{

class DIGITALFILTERS_MODULE_LIB IIRfreqResponse
{
public:

	static std::complex<double> EvalBicuad(
		const BicuadCoefficients& coef,
		double freq, double fs);

	static std::complex<double> EvalBicuad(
		double a0, double a1, double a2,
		double b1, double b2,
		double freq, double fs);

	static std::complex<double> FrequencyResponse(
		const std::vector<double>& zeros,
		const std::vector<double>& poles,
		double freq, double fs);

	static std::vector < std::complex<double> >FrequencyResponse(
		const std::vector<double>& zeros,
		const std::vector<double>& poles,
		const std::vector<double>& freqs, double fs);

	static std::pair<double, double> EvalBicuadTrig(
		const BicuadCoefficients& coef,
		double freq, double fs);

	static std::pair<double, double> EvalBicuadTrig(
		double a0, double a1, double a2,
		double b1, double b2,
		double freq, double fs);

	static std::pair< double, double>FrequencyResponseTrig(
		const std::vector<double>& zeros,
		const std::vector<double>& poles,
		double freq, double fs);

	static std::vector < std::pair< double, double> >FrequencyResponseTrig(
		const std::vector<double>& zeros,
		const std::vector<double>& poles,
		const std::vector<double>& freqs, double fs);

	static double GainTodB(double);

	static double HzToW(double);

};

};
