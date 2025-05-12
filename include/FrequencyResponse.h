#pragma once
#include <type_traits>
#include <cmath> // For std::abs

namespace DigitalFilters {

	template <typename T> requires std::is_floating_point_v<T>
	struct FrequencyResponse
	{
		T magnitude; // |H(w)|
		T phase;     //  H(w), in radians

		// Default constructor
		FrequencyResponse() : magnitude( 0.0 ), phase( 0.0 ) {}

		// Constructor with initial values
		FrequencyResponse( T mag, T ph ) : magnitude( mag ), phase( ph ) {}

		// Copy constructor
		FrequencyResponse( const FrequencyResponse& other ) :
			magnitude( other.magnitude ), phase( other.phase ) {
		}

		// Move constructor
		FrequencyResponse( FrequencyResponse&& other ) noexcept :
			magnitude( other.magnitude ), phase( other.phase )
		{
			other.magnitude = 0.0;
			other.phase = 0.0;
		}

		// Copy assignment operator
		FrequencyResponse& operator=( const FrequencyResponse& other )
		{
			if (this != &other)
			{
				magnitude = other.magnitude;
				phase = other.phase;
			}
			return *this;
		}

		// Move assignment operator
		FrequencyResponse& operator=( FrequencyResponse&& other ) noexcept
		{
			if (this != &other)
			{
				magnitude = other.magnitude;
				phase = other.phase;
				other.magnitude = 0.0;
				other.phase = 0.0;
			}
			return *this;
		}

		// Comparison operator for magnitude
		bool operator==( const FrequencyResponse& other ) const
		{
			// Consider using a small epsilon for floating-point comparisons
			return
				std::abs( magnitude - other.magnitude )
				< std::numeric_limits<T>::epsilon()
				&&
				std::abs( phase - other.phase )
				< std::numeric_limits<T>::epsilon();
		}

	};

}
