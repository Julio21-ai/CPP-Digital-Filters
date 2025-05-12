#pragma once
#include <complex>
#include <vector>
#include "..\include\Biquad.h"
#include "..\include\FrequencyResponse.h"
#include "DigitalFiltersModuleExport.h"


using namespace DigitalFilters;
using BiquadCoefficientsDouble = Biquad<double>;
using FrequencyResponseDouble = FrequencyResponse<double>;

namespace DigitalFilters
{

class DIGITALFILTERS_MODULE_LIB IIRfreqResponse
{
public:

	static std::complex<double> EvalBicuad(
		const BiquadCoefficientsDouble& coef,
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

	static FrequencyResponseDouble EvalBicuadTrig(
		const BiquadCoefficientsDouble& coef,
		double freq, double fs);

	static FrequencyResponseDouble EvalBicuadTrig(
		double a0, double a1, double a2,
		double b1, double b2,
		double freq, double fs);

	static FrequencyResponseDouble FrequencyResponseTrig(
		const std::vector<double>& zeros,
		const std::vector<double>& poles,
		double freq, double fs);

	static std::vector < FrequencyResponseDouble >FrequencyResponseTrig(
		const std::vector<double>& zeros,
		const std::vector<double>& poles,
		const std::vector<double>& freqs, double fs);


};

};
