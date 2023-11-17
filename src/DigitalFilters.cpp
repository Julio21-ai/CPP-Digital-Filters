
#include <DigitalFilters.h>
#include <math.h>
#include <complex>
#include <sstream>

#include <math.h>
/*==============================================================================
**
** Internal helper functions and constants
**
*/

//static const long double pi    = 3.14159265358979323846264338327950288419716939937510L;
//static const long double sqrt2 = 1.41421356237309504880168872420969807856967187537694L;
//
//template<typename T>
//__forceinline T FreqToW(T freq, T sampleRate)
//{
//	return  2 * pi * freq / sampleRate;
//}
//
//// Convert magnitude to decibels
//template<typename T>
// T GainTodB(T magnitude)
//{
//	return  20 * log10(magnitude);
//}
//
//
///*==============================================================================
//**
//** Evaluate filter responses in dB
//**
//*/
//
//#pragma region EvalBicuadFilterResponseDbTrig()
// std::pair< long double, long double> EvalBicuadFilterResponseDbTrig(
//	 long double fc
//	 , long double fs
//	 , BicuadCoefficients& Coef)
// {
//	 std::pair< long double, long double>  Hw = TEvalBicuadTrig(
//		 (long double)Coef.a0, (long double)Coef.a1, (long double)Coef.a2,
//		 (long double)Coef.b1, (long double)Coef.b2,
//		 FreqToW(fc, fs));
//
//	 return std::pair<long double, long double>(GainTodB(Hw.first), Hw.second);
// }
//#pragma endregion
//
//#pragma region EvalBicuadFilterResponseDb()
// std::pair< long double, long double>EvalBicuadFilterResponseDb(
//	 long double fc
//	 , long double fs
//	 , BicuadCoefficients& Coef)
// {
//	 auto Hw = TEvalBicuad(
//		 (long double)Coef.a0, (long double)Coef.a1, (long double)Coef.a2,
//		 (long double)Coef.b1, (long double)Coef.b2,
//		 FreqToW(fc, fs));
//
//	 auto magnitude_db = 20L * log10(abs(Hw));
//	 auto phase = arg(Hw);
//
//	 return std::pair<double, double>(magnitude_db, phase);
// }
//
//#pragma endregion
//
///*
//**
//**Evaluate filter responses in linear units
//**
//*/
//
//#pragma region FrequencyResponseTrig()
//std::pair<long double, long double> FrequencyResponseTrig(
//	const long double* zeros
//	, const long double* poles
//	, int filterOrder
//	, long double w
//)
//{
//	return TFrequencyResponseTrig(zeros, poles, filterOrder, w);
//}
//#pragma endregion
//
//#pragma region FrequencyResponse()
//std::complex<long double> FrequencyResponse(const long double* zeros
//	, const long double* poles
//	, int filterOrder
//	, long double w
//)
//{
//	return TFrequencyResponse(zeros, poles, filterOrder, w);
//}
//#pragma endregion
//
//
