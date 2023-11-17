#pragma once

#include <math.h>

#ifndef DIGITALFILTERS_STATIC_LIB
#if defined(DIGITALFILTERS_EXPORTS)
#define DIGITALFILTERS_MODULE_LIB __declspec(dllexport)
#else
#define DIGITALFILTERS_MODULE_LIB __declspec(dllimport)
#endif
#else
#define DIGITALFILTERS_MODULE_LIB 
#endif

namespace DigitalFilters
{
// Math constants adequate for computation using `long double's
class DIGITALFILTERS_MODULE_LIB MathConstants
{
public:
    // e 
    static constexpr long double e =
        2.718281828459045235360287471352662498L;

    // log2 e 
    static constexpr long double log2e =
        1.442695040888963407359924681001892137L;

    // log10 e
    static constexpr long double log10e = 
        0.434294481903251827651128918916605082L;

    // ln 2
    static constexpr long double ln2 =
        0.693147180559945309417232121458176568L;

    // ln 10
    static constexpr long double  ln10 =
        2.302585092994045684017991454684364208L;

    // pi
    static constexpr long double pi =
        3.141592653589793238462643383279502884L;

     // pi/2
    static constexpr long double  pi_2 =
        1.570796326794896619231321691639751442L;

    //pi/4
    static constexpr long double  pi_4 =
        0.785398163397448309615660845819875721L;

    // 2*Pi
    static constexpr long double  m_pi2 =
        6.283185307179586476925286766559005768L;

    // 1/pi 
    static constexpr long double  m_1_pi =
        0.318309886183790671537767526745028724L;

    // 2/pi 
    static constexpr long double  m_2_pi =
        0.636619772367581343075535053490057448L;

    // 2/sqrt(pi)
    static constexpr long double m_2_SqrtPi =
        1.128379167095512573896158903121545172L;

    // sqrt(2)
    static constexpr long double sqrt2 = 
        1.414213562373095048801688724209698079L;

    // 1/sqrt(2)
    static constexpr long double m_1_Sqrt2 =
        0.707106781186547524400844362104849039L;

};

// Math constants adequate for computation using float
class DIGITALFILTERS_MODULE_LIB MathConstantsf
{
public:

  // e 
  static constexpr float e =
    2.7182818284590452354f;

  // log2 e 
  static constexpr float log2e =
    1.4426950408889634074f;

  // log10 e
  static constexpr float log10e =
    0.43429448190325182765f;

  // ln 2
  static constexpr float ln2 =
    0.69314718055994530942f;

  // ln 10
  static constexpr float  ln10 =
    2.30258509299404568402f;

  // pi
  static constexpr float pi =
    3.14159265358979323846f;

  // pi/2
  static constexpr long double  pi_2 =
    1.57079632679489661923f;

  //pi/4
  static constexpr long double  pi_4 =
    0.78539816339744830962f;

  // 2*Pi
  static constexpr long double  m_pi2 =
    6.28318530717958647693f;

  // 1/pi 
  static constexpr long double  m_1_pi =
    0.31830988618379067154f;

  // 2/pi 
  static constexpr long double  m_2_pi =
    0.63661977236758134308f;

  // 2/sqrt(pi)
  static constexpr long double m_2_SqrtPi =
    1.12837916709551257390f;

  // sqrt(2)
  static constexpr long double sqrt2 =
    1.41421356237309504880f;

  // 1/sqrt(2)
  static constexpr long double m_1_Sqrt2 =
    0.70710678118654752440f;

};

}