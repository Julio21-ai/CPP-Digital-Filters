// IIRFiltersDesignExport.cpp
#include "Biquad.h"
#include "IIRDesign.h"

using namespace DigitalFilters;
using BiquadCoefficientsd = Biquad<double>;



namespace DigitalFilters {

	template Biquad<double> IIR::HighShelf1stOrder<double>( double, double, double );
	template Biquad<double> IIR::LowShelf1stOrder<double>( double, double, double );
	template Biquad<double> IIR::HighPass1stOrder<double>( double, double );
	template Biquad<double> IIR::AllPass1stOrder<double>( double, double );
	template Biquad<double> IIR::PeakEq<double>( double, double, double, double );

}
