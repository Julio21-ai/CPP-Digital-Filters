
#include <DigitalFilters.h>
#include <math.h>
#include <complex>
#include <sstream>

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES 
#endif

#include <math.h>

/*==============================================================================
**
** Helper functions
**
*/

inline void evalCoeffs(double w, const double* coeffs, int ncoefs
													, std::complex<double>& res)
{
	using namespace std;
  res = 0;

	for( int idx = 0; idx < ncoefs; idx++ )
	{
		complex<double> njw( 0, -idx * w );
		res += coeffs[idx] * exp( njw );
	}

}

double FreqToW( double freq,double sampleRate )
{
	return  2 * M_PI * freq / sampleRate;
}

double GainTodB( double magnitude )
{
	return  20 * log10( magnitude );
}

__forceinline double To_dB( double magnitude)
{
	return  20 * log10( magnitude );
}

__forceinline double To_w( double freq, double sampleRate )
{
	return  2 * M_PI * freq / sampleRate;;
}

/*==============================================================================
**
** Evaluate fiter responses in dB
**
*/

void dBEvalFilter( double freq
								 , double sampleRate
								 , const filterCoefficients& Coef
								 , double& magnitude_db
								 , double& phase )
{
	double w = 2 * M_PI * freq / sampleRate;
	EvalBicuad( w, Coef, magnitude_db, phase );
	magnitude_db =	To_dB( magnitude_db );
}

void dBEvalFilterComplex( double freq
												, double sampleRate
												, const filterCoefficients& Coef
												, double& magnitude_dB
												, double& phase )
{
	double w = 2 * M_PI * freq / sampleRate;
	EvalBicuadComplex( w, Coef, magnitude_dB, phase );
	magnitude_dB = To_dB( magnitude_dB );
}

double EvalFreqResponseDB(double freq
												 , double sampleRate
												 , const filterCoefficients& Coef)
{

	double magnitude;//gain in Au
	double phase;

	dBEvalFilter(freq, sampleRate, Coef, magnitude, phase);
	return magnitude;

}

double EvalFreqResponseDbComplex( double freq
																	, double sampleRate
																	, const filterCoefficients& Coef )
{
	double magnitude;//gain in Au
	double phase;

	dBEvalFilterComplex( freq, sampleRate, Coef, magnitude, phase );
	return  magnitude;
}

/*==============================================================================
**
** Evaluate bicuads
**
*/

void EvalBicuad( double w
								 , const filterCoefficients& Coef
								 , double& magnitude
								 , double& phase )
{
	double cos1 = cos( -1 * w );
	double cos2 = cos( -2 * w );

	double sin1 = sin( -1 * w );
	double sin2 = sin( -2 * w );

	double realZeros = Coef.a0 + Coef.a1 * cos1 + Coef.a2 * cos2;
	double imagZeros = Coef.a1 * sin1 + Coef.a2 * sin2;

	double realPoles = 1 + Coef.b1 * cos1 + Coef.b2 * cos2;
	double imagPoles = Coef.b1 * sin1 + Coef.b2 * sin2;

	double divider = realPoles * realPoles + imagPoles * imagPoles;

	double realHw = (realZeros * realPoles + imagZeros * imagPoles) / divider;
	double imagHw = (imagZeros * realPoles - realZeros * imagPoles) / divider;


	magnitude = sqrt( realHw * realHw + imagHw * imagHw );

	phase = atan2( imagHw, realHw );
}


void EvalBicuadComplex( double w
												, const filterCoefficients& Coef
												, double& magnitude
												, double& phase )
{
	using namespace std;

	complex<double> Hw =
		(Coef.a0
			+ Coef.a1 * (exp( complex<double>( 0, -1 * (w) ) ))
			+ Coef.a2 * (exp( complex<double>( 0, -2 * (w) ) ))
			)
		/
		(1.0
			+ Coef.b1 * (exp( complex<double>( 0, -1 * w ) ))
			+ Coef.b2 * (exp( complex<double>( 0, -2 * w ) ))
			);

	magnitude = abs( Hw );
	phase = arg( Hw );

}


void FilterDirectEval( double w
								 , const double* a_coeffs
								 , const double* b_coeffs
								 , int nCoeffs
								 , double& magnitude
								 , double& phase )
{
	using namespace std;

	complex<double> resZeros;
	complex<double> resPoles;
	complex<double> compexRes;

	evalCoeffs( w, a_coeffs, nCoeffs, resZeros );
	evalCoeffs( w, b_coeffs, nCoeffs, resPoles );

	compexRes = resZeros / resPoles;

	magnitude = abs( compexRes );
	phase = arg( compexRes );

}

/*==============================================================================
**
** Calculate Coefficients for the filters
**
*/

void onepole_lpCoefficients(double peakGain
														, double Fc
														, double Fs
														, filterCoefficients& coef)
{

	double V = pow(10, fabs(peakGain) / 20);
	double K = tan(M_PI * Fc / Fs);

	coef.b1 = exp(-2.0 * M_PI * (Fc / Fs));
	coef.a0 = 1.0 - coef.b1;
	coef.b1 = -coef.b1;
	coef.a1 = coef.a2 = coef.b2 = 0;

}

void ononepole_hpCoefficients(double peakGain
															, double Fc
															, double Fs
															, filterCoefficients& coef)
{
	double V = pow(10, fabs(peakGain) / 20);
	double K = tan(M_PI * Fc / Fs);


	coef.b1 = -exp(-2.0 * M_PI * (0.5 - Fc / Fs)); //dubious -exp
	coef.a0 = 1.0 + coef.b1;
	coef.b1 = -coef.b1;
	coef.a1 = coef.a2 = coef.b2 = 0;
}

void lowpassCoefficients(double peakGain
												 , double Fc
												 , double Q
												 , double Fs
												 , filterCoefficients& coef)
{
	double V = pow(10, fabs(peakGain) / 20);
	double K = tan(M_PI * Fc / Fs);
	double norm;

	norm = 1 / (1 + K / Q + K * K);
	coef.a0 = K * K * norm;
	coef.a1 = 2 * coef.a0;
	coef.a2 = coef.a0;
	coef.b1 = 2 * (K * K - 1) * norm;
	coef.b2 = (1 - K / Q + K * K) * norm;
}

void highpassCoefficients(double peakGain
													, double Fc
													, double Q
													, double Fs
													, filterCoefficients& coef)
{
	double norm;
	double V = pow(10, fabs(peakGain) / 20);
	double K = tan(M_PI * Fc / Fs);

	norm = 1 / (1 + K / Q + K * K);
	coef.a0 = 1 * norm ;
	coef.a1 = -2 * coef.a0;
	coef.a2 = coef.a0;
	coef.b1 = 2 * (K * K - 1) * norm;
	coef.b2 = (1 - K / Q + K * K) * norm;

}

void bandpassCoefficients(double peakGain
													, double Fc
													, double Q
													, double Fs
													, filterCoefficients& coef)
{

	double K = tan(M_PI * Fc / Fs);
	double norm;
	norm = 1 / (1 + K / Q + K * K);
	coef.a0 = K / Q * norm;
	coef.a1 = 0;
	coef.a2 = -coef.a0;
	coef.b1 = 2 * (K * K - 1) * norm;
	coef.b2 = (1 - K / Q + K * K) * norm;
}

void notchCoefficients(double peakGain
											 , double Fc
											 , double Q
											 , double Fs
											 , filterCoefficients& coef)
{
	double norm;
	double K = tan(M_PI * Fc / Fs);

	norm = 1 / (1 + K / Q + K * K);
	coef.a0 = (1 + K * K) * norm;
	coef.a1 = 2 * (K * K - 1) * norm;
	coef.a2 = coef.a0;
	coef.b1 = coef.a1;
	coef.b2 = (1 - K / Q + K * K) * norm;
}

void peakCoefficients(double peakGain
											, double Fc
											, double Q
											, double Fs
											, filterCoefficients& coef)
{
	double norm;
	double V = pow(10, fabs(peakGain) / 20);
	double K = tan(M_PI * Fc / Fs);

	if( peakGain >= 0 )
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
}



void highShelfCoefficients(double peakGain
													 , double Fc
													 , double Fs
													 , filterCoefficients& coef)
{
	double norm;
	double V = pow(10, fabs(peakGain) / 20);
	double K = tan(M_PI * Fc / Fs);


	if( peakGain >= 0 )
	{
		norm = 1 / (1 + M_SQRT2 * K + K * K);
		coef.a0 = (V + sqrt(2 * V) * K + K * K) * norm;
		coef.a1 = 2 * (K * K - V) * norm;
		coef.a2 = (V - sqrt(2 * V) * K + K * K) * norm;
		coef.b1 = 2 * (K * K - 1) * norm;
		coef.b2 = (1 - M_SQRT2 * K + K * K) * norm;
	}
	else {
		norm = 1 / (V + sqrt(2 * V) * K + K * K);
		coef.a0 = (1 + M_SQRT2 * K + K * K) * norm;
		coef.a1 = 2 * (K * K - 1) * norm;
		coef.a2 = (1 - M_SQRT2 * K + K * K) * norm;
		coef.b1 = 2 * (K * K - V) * norm;
		coef.b2 = (V - sqrt(2 * V) * K + K * K) * norm;
	}

}

void highShelfCoefficients( double peakGain
														, double Fc
														, double Q
														, double Fs
														, filterCoefficients& coef )
{
	double norm;
	double V = pow( 10, fabs( peakGain ) / 20 );
	double K = tan( M_PI * Fc / Fs );


	if( peakGain >= 0 )
	{
		norm = 1 / (1 + 1 / Q * K + K * K);
		coef.a0 = (V + sqrt( 2 * V ) * K + K * K) * norm;
		coef.a1 = 2 * (K * K - V) * norm;
		coef.a2 = (V - sqrt( 2 * V ) * K + K * K) * norm;
		coef.b1 = 2 * (K * K - 1) * norm;
		coef.b2 = (1 - 1 / Q * K + K * K) * norm;
	}
	else
	{
		norm = 1 / (V + sqrt( 2 * V ) * K + K * K);
		coef.a0 = (1 + 1 / Q * K + K * K) * norm;
		coef.a1 = 2 * (K * K - 1) * norm;
		coef.a2 = (1 - 1 / Q * K + K * K) * norm;
		coef.b1 = 2 * (K * K - V) * norm;
		coef.b2 = (V - sqrt( 2 * V ) * K + K * K) * norm;
	}

}

void lowShelfCoefficients( double peakGain
													 , double Fc
													 , double Fs
													 , filterCoefficients& coef )
{
	double norm;
	double V = pow( 10, fabs( peakGain ) / 20 );
	double K = tan( M_PI * Fc / Fs );

	if( peakGain >= 0 )
	{
		norm = 1 / (1 + M_SQRT2 * K + K * K);
		coef.a0 = (1 + sqrt( 2 * V ) * K + V * K * K) * norm;
		coef.a1 = 2 * (V * K * K - 1) * norm;
		coef.a2 = (1 - sqrt( 2 * V ) * K + V * K * K) * norm;
		coef.b1 = 2 * (K * K - 1) * norm;
		coef.b2 = (1 - M_SQRT2 * K + K * K) * norm;
	}
	else
	{
		norm = 1 / (1 + sqrt( 2 * V ) * K + V * K * K);
		coef.a0 = (1 + M_SQRT2 * K + K * K) * norm;
		coef.a1 = 2 * (K * K - 1) * norm;
		coef.a2 = (1 - M_SQRT2 * K + K * K) * norm;
		coef.b1 = 2 * (V * K * K - 1) * norm;
		coef.b2 = (1 - sqrt( 2 * V ) * K + V * K * K) * norm;
	}
}

void lowShelfCoefficients( double peakGain
													 , double Fc
													 , double Q
													 , double Fs
													 , filterCoefficients& coef )
{
	double norm;
	double V = pow( 10, fabs( peakGain ) / 20 );
	double K = tan( M_PI * Fc / Fs );

	if( peakGain >= 0 )
	{    // boost
		norm = 1 / (1 + 1 / Q * K + K * K);
		coef.a0 = (1 + sqrt( V ) / Q * K + V * K * K) * norm;
		coef.a1 = 2 * (V * K * K - 1) * norm;
		coef.a2 = (1 - sqrt( V ) / Q * K + V * K * K) * norm;
		coef.b1 = 2 * (K * K - 1) * norm;
		coef.b2 = (1 - 1 / Q * K + K * K) * norm;
	}
	else
	{    // cut
		norm = 1 / (1 + sqrt( V ) / Q * K + V * K * K);
		coef.a0 = (1 + 1 / Q * K + K * K) * norm;
		coef.a1 = 2 * (K * K - 1) * norm;
		coef.a2 = (1 - 1 / Q * K + K * K) * norm;
		coef.b1 = 2 * (V * K * K - 1) * norm;
		coef.b2 = (1 - sqrt( V ) / Q * K + V * K * K) * norm;
	}

}
