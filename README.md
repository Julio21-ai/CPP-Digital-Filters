# CPP-Digital-Filters
"Implementation of a Biquad IIR commonly used Filter in C++"

This header project provides functions and structures for evaluating digital filters and biquads coefficients.

## Usage

To use the functions in this header file, include it in your C++ project and link against the appropriate library (if required).

### Functions

- `dBEvalFilter`: Evaluates the magnitude and phase response of a filter at a given frequency.
- `dBEvalFilterComplex`: Evaluates the complex magnitude and phase response of a filter at a given frequency.
- `EvalFreqResponseDB`: Evaluates the magnitude response of a filter at a given frequency in decibels.
- `EvalFreqResponseDbComplex`: Evaluates the complex magnitude response of a filter at a given frequency in decibels.
- `EvalBicuad`: Evaluates the magnitude and phase response of a biquad filter at a given frequency.
- `EvalBicuadComplex`: Evaluates the complex magnitude and phase response of a biquad filter at a given frequency.
- `FilterDirectEval`: Evaluates the magnitude and phase response of a filter using direct coefficients.

### Coefficients Calculation

- `bandpassCoefficients`: Calculates coefficients for a bandpass filter.
- `highpassCoefficients`: Calculates coefficients for a highpass filter.
- `highShelfCoefficients`: Calculates coefficients for a high-shelf filter.
- `lowpassCoefficients`: Calculates coefficients for a lowpass filter.
- `lowShelfCoefficients`: Calculates coefficients for a low-shelf filter.
- `notchCoefficients`: Calculates coefficients for a notch filter.
- `onepole_lpCoefficients`: Calculates coefficients for a one-pole lowpass filter.
- `ononepole_hpCoefficients`: Calculates coefficients for a one-pole highpass filter.
- `peakCoefficients`: Calculates coefficients for a peak filter.

### Helpers

- `FreqToW`: Converts a frequency value to angular frequency.
- `GainTodB`: Converts a gain value to decibels.

## References

For more detailed information, references, and excelent examples, visit [EarLevel's Biquad Formulas](http://www.earlevel.com/main/2011/01/02/biquad-formulas/).

Thanks

Julio Baltazar
