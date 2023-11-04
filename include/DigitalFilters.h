#pragma once
#pragma once
#ifndef id18AE01D7_FCD3_45B6_91CE252D0A9B58A0
#define id18AE01D7_FCD3_45B6_91CE252D0A9B58A0
/*
**
**  implements functions for evaluate digital filters and biquads coefficients
** more references and examples can be found at
** http://www.earlevel.com/main/2011/01/02/biquad-formulas/
**
**
*/
#ifndef DIGITALFILTERS_STATIC_LIB
	#if defined(DIGITALFILTERS_EXPORTS)
	#define DIGITALFILTERS_MODULE_LIB __declspec(dllexport)
	#else
	#define DIGITALFILTERS_MODULE_LIB __declspec(dllimport)
	#endif
	#else
#define DIGITALFILTERS_MODULE_LIB 
#endif

	struct DIGITALFILTERS_MODULE_LIB filterCoefficients
	{
		double a0, a1, a2, b1, b2;
	};


	/*
	******************************************************************************
	** evaluate de Coefficients
	******************************************************************************
	*/


	DIGITALFILTERS_MODULE_LIB
		void dBEvalFilter( double freq
										 , double sampleRate
										 , const filterCoefficients& Coef
										 , double& magnitude_dB
										 , double& phase );

	DIGITALFILTERS_MODULE_LIB
		void dBEvalFilterComplex( double freq
														, double sampleRate
														, const filterCoefficients& Coef
														, double& magnitude_dB
														, double& phase );

	DIGITALFILTERS_MODULE_LIB
		double EvalFreqResponseDB( double freq
															 , double sampleRate
															 , const filterCoefficients& Coef );
	DIGITALFILTERS_MODULE_LIB
		double EvalFreqResponseDbComplex( double freq
																			, double sampleRate
																			, const filterCoefficients& Coef );

	DIGITALFILTERS_MODULE_LIB
		void EvalBicuad( double w
										 , const filterCoefficients& Coef
										 , double& magnitude
										 , double& phase );

	DIGITALFILTERS_MODULE_LIB
		void EvalBicuadComplex( double w
														, const filterCoefficients& Coef
														, double& magnitude
														, double& phase );


	DIGITALFILTERS_MODULE_LIB
		void FilterDirectEval( double w
													 , const double* a_coeffs
													 , const double* b_coeffs
													 , int nCoeffs
													 , double& magnitude
													 , double& phase );

	/*
	******************************************************************************
	** Calculate Coefficients for the filters
	******************************************************************************
	*/
	DIGITALFILTERS_MODULE_LIB
		void bandpassCoefficients( double peakGain
															 , double Fc
															 , double Q
															 , double Fs
															 , filterCoefficients& coef );

	DIGITALFILTERS_MODULE_LIB
		void highpassCoefficients( double peakGain
															 , double Fc
															 , double Q
															 , double Fs
															 , filterCoefficients& coef );

	DIGITALFILTERS_MODULE_LIB
		void highShelfCoefficients( double peakGain
																, double Fc
																, double Fs
																, filterCoefficients& coef );

	DIGITALFILTERS_MODULE_LIB
		void highShelfCoefficients( double peakGain
																, double Fc
																, double Q
																, double Fs
																, filterCoefficients& coef );

	DIGITALFILTERS_MODULE_LIB
		void lowpassCoefficients( double peakGain
															, double Fc
															, double Q
															, double Fs
															, filterCoefficients& coef );

	DIGITALFILTERS_MODULE_LIB
		void lowShelfCoefficients( double peakGain
															 , double Fc
															 , double Q
															 , double Fs
															 , filterCoefficients& coef );

	DIGITALFILTERS_MODULE_LIB
		void lowShelfCoefficients( double peakGain
															 , double Fc
															 , double Fs
															 , filterCoefficients& coef );

	DIGITALFILTERS_MODULE_LIB
		void notchCoefficients( double peakGain
														, double Fc
														, double Q
														, double Fs
														, filterCoefficients& coef );


	DIGITALFILTERS_MODULE_LIB
		void onepole_lpCoefficients( double peakGain
																 , double Fc
																 , double Fs
																 , filterCoefficients& coef );

	DIGITALFILTERS_MODULE_LIB
		void ononepole_hpCoefficients( double peakGain
																	 , double Fc
																	 , double Fs
																	 , filterCoefficients& coef );

	DIGITALFILTERS_MODULE_LIB
		void peakCoefficients( double peakGain
													 , double Fc
													 , double Q
													 , double Fs
													 , filterCoefficients& coef );

	/*
	******************************************************************************
	** Helpers
	******************************************************************************
	*/

	DIGITALFILTERS_MODULE_LIB
	double FreqToW( double Fc, double Fs );

	double GainTodB( double magnidude );


#endif // header