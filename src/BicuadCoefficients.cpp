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
