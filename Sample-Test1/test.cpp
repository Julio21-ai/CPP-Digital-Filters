#include "pch.h"
#include <math.h>
#include <iostream>
#include <complex>
#include "..\include\DigitalFilters.h"
#include <random>
#include <chrono>
#include "..\include\IIRfreqResponse.h"
#include "..\include\IIRFilters.h"
#include "../include/FilterUtils.h"

using namespace DigitalFilters;

long  double Epsilon = 8.8817841970012523e-15;

typedef union
{
  long long i64;
  double d64;
} dbl_64;


  double machine_eps(double value)
  {
    dbl_64 s;
    s.d64 = value;
    s.i64++;
    return s.d64 - value;
  }


  double absErr(double x, double y)
  {
     return abs( x-y) / x;
  }


  std::vector<double> generateRandomFloats(int count)
  {
    std::vector<double> randomFloats;

    // Configura el generador de números aleatorios
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(20.0f, 500.0f);

    // Genera valores flotantes aleatorios y los agrega al vector
    for(int i = 0; i < count; ++i)
    {
      randomFloats.push_back(dis(gen));
    }

    return randomFloats;
  }

  std::vector<double> randomSet = generateRandomFloats(44800000);

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(DigitalFiltersTEST, TEST_LowShelf1stOrder)
{
    using namespace DigitalFilters;

    BicuadCoefficients bicuads;

    bicuads = IIRFilters::LowShelf1stOrder(5, 100, 1000);

    ASSERT_NEAR(bicuads.getA0(), 1.1908631219032908, Epsilon);
    ASSERT_NEAR(bicuads.getA1(), -0.31866232759113794, Epsilon);
    ASSERT_NEAR(bicuads.getA2(), 0, Epsilon);

    ASSERT_NEAR(bicuads.getB1(), -0.5095254494944288, Epsilon);
    ASSERT_NEAR(bicuads.getB2(), 0, Epsilon);

}

TEST(DigitalFiltersTEST, TEST_HighShelf1stOrder)
{
    using namespace DigitalFilters;

    BicuadCoefficients bicuads;

    bicuads = IIRFilters::HighShelf1stOrder(5, 100, 1000);

    ASSERT_NEAR(bicuads.getA0(), 1.587416288135632,Epsilon);
    ASSERT_NEAR(bicuads.getA1(), -1.0969417376300605, Epsilon);
    ASSERT_NEAR(bicuads.getA2(), 0, Epsilon);

    ASSERT_NEAR(bicuads.getB1(), -0.5095254494944288, Epsilon);
    ASSERT_NEAR(bicuads.getB2(), 0, Epsilon);

}

TEST(DigitalFiltersTEST, TEST_HighPass1stOrder)
{
    using namespace DigitalFilters;

    BicuadCoefficients bicuads;

    bicuads = IIRFilters::HighPass1stOrder(100, 1000);

    ASSERT_NEAR(bicuads.getA0(), 0.7547627247472144, Epsilon);
    ASSERT_NEAR(bicuads.getA1(), -0.7547627247472144, Epsilon);
    ASSERT_NEAR(bicuads.getA2(), 0, Epsilon);

    ASSERT_NEAR(bicuads.getB1(), -0.5095254494944288, Epsilon);
    ASSERT_NEAR(bicuads.getB2(), 0, Epsilon);

}

TEST(DigitalFiltersTEST, TEST_LowPass1stOrder)
{
    using namespace DigitalFilters;

    BicuadCoefficients bicuads;

    bicuads = IIRFilters::LowPass1stOrder( 100, 1000);

    ASSERT_NEAR(bicuads.getA0(), 0.24523727525278555, Epsilon);
    ASSERT_NEAR(bicuads.getA1(), 0.24523727525278555, Epsilon);
    ASSERT_NEAR(bicuads.getA2(), 0, Epsilon);

    ASSERT_NEAR(bicuads.getB1(), -0.5095254494944289, Epsilon);
    ASSERT_NEAR(bicuads.getB2(), 0, Epsilon);

}

TEST(DigitalFiltersTEST, TEST_AllPass)
{
    using namespace DigitalFilters;

    BicuadCoefficients bicuads;

    bicuads = IIRFilters::AllPass1stOrder( 100, 1000);

    ASSERT_NEAR(bicuads.getA0(), 0.5095254494944288, Epsilon);
    ASSERT_NEAR(bicuads.getA1(), -1, Epsilon);
    ASSERT_NEAR(bicuads.getA2(), 0, Epsilon);

    ASSERT_NEAR(bicuads.getB1(), -0.5095254494944288, Epsilon);
    ASSERT_NEAR(bicuads.getB2(), 0, Epsilon);

}


TEST(DigitalFiltersTEST, TEST_AllPassQ)
{
    using namespace DigitalFilters;

    BicuadCoefficients bicuads;

    bicuads = IIRFilters::AllPassQ(100, 10, 1000);

    ASSERT_NEAR(bicuads.getA0(), 0.9428996130385592 , Epsilon);
    ASSERT_NEAR(bicuads.getA1(), -1.5718388053127037, Epsilon);
    ASSERT_NEAR(bicuads.getA2(), 1                  , Epsilon);

    ASSERT_NEAR(bicuads.getB1(), -1.5718388053127037, Epsilon);
    ASSERT_NEAR(bicuads.getB2(), 0.9428996130385592, Epsilon);

}



TEST(DigitalFiltersTEST, TEST_BandPass)
{
    using namespace DigitalFilters;

    BicuadCoefficients bicuads;

    bicuads = IIRFilters::BandPass(100, 10, 1000);

    ASSERT_NEAR(bicuads.getA0(), 0.028550193480720448, Epsilon);
    ASSERT_NEAR(bicuads.getA1(), 0, Epsilon);
    ASSERT_NEAR(bicuads.getA2(), -0.028550193480720448, Epsilon);

    ASSERT_NEAR(bicuads.getB1(), -1.5718388053127037, Epsilon);
    ASSERT_NEAR(bicuads.getB2(), 0.9428996130385592, Epsilon);

}



TEST(DigitalFiltersTEST, TEST_HighPass)
{
    using namespace DigitalFilters;

    BicuadCoefficients bicuads;

    bicuads = IIRFilters::HighPass( 100,10 , 1000);

    ASSERT_NEAR(bicuads.getA0(), 0.8786846045878157, Epsilon);
    ASSERT_NEAR(bicuads.getA1(), -1.7573692091756314, Epsilon);
    ASSERT_NEAR(bicuads.getA2(), 0.8786846045878157, Epsilon);

    ASSERT_NEAR(bicuads.getB1(), -1.5718388053127037, Epsilon);
    ASSERT_NEAR(bicuads.getB2(), 0.9428996130385592, Epsilon);

}


TEST(DigitalFiltersTEST, TEST_HighShelf)
{
    using namespace DigitalFilters;

    BicuadCoefficients bicuads;

    bicuads = IIRFilters::HighShelf(5, 100,  1000);

    ASSERT_NEAR(bicuads.getA0(), 1.595199772351261, Epsilon);
    ASSERT_NEAR(bicuads.getA1(), -2.1375367952754485, Epsilon);
    ASSERT_NEAR(bicuads.getA2(), 0.8121581184804753, Epsilon);

    ASSERT_NEAR(bicuads.getB1(), -1.1429805025399011, Epsilon);
    ASSERT_NEAR(bicuads.getB2(), 0.4128015980961886, Epsilon);

}


TEST(DigitalFiltersTEST, TEST_HighShelfQ)
{
    using namespace DigitalFilters;

    BicuadCoefficients bicuads;

    bicuads = IIRFilters::HighShelfQ(5, 100, 1 / sqrt(2), 1000);

    ASSERT_NEAR(bicuads.getA0(), 1.595199772351261, Epsilon);
    ASSERT_NEAR(bicuads.getA1(), -2.1375367952754485, Epsilon);
    ASSERT_NEAR(bicuads.getA2(), 0.8121581184804753, Epsilon);

    ASSERT_NEAR(bicuads.getB1(), -1.1429805025399011, Epsilon);
    ASSERT_NEAR(bicuads.getB2(), 0.4128015980961886, Epsilon);

}


TEST(DigitalFiltersTEST, TEST_LowShelf)
{
    using namespace DigitalFilters;

    BicuadCoefficients bicuads;

    bicuads = IIRFilters::LowShelf(5, 100,  1000);

    ASSERT_NEAR(bicuads.getA0(), 1.1504206767498881, Epsilon);
    ASSERT_NEAR(bicuads.getA1(), -1.0379824010070995, Epsilon);
    ASSERT_NEAR(bicuads.getA2(), 0.3673790228791024, Epsilon);

    ASSERT_NEAR(bicuads.getB1(), -1.1429805025399011, Epsilon);
    ASSERT_NEAR(bicuads.getB2(), 0.4128015980961886, Epsilon);

}

TEST(DigitalFiltersTEST, TEST_LowShelfQ)
{
    using namespace DigitalFilters;

    BicuadCoefficients bicuads;

    bicuads = IIRFilters::LowShelfQ(5, 100, 1 / sqrt(2), 1000);


    ASSERT_NEAR(bicuads.getA0(), 1.1504206767498881, Epsilon);
    ASSERT_NEAR(bicuads.getA1(), -1.0379824010070995, Epsilon);
    ASSERT_NEAR(bicuads.getA2(), 0.3673790228791024, Epsilon);

    ASSERT_NEAR(bicuads.getB1(), -1.1429805025399011, Epsilon);
    ASSERT_NEAR(bicuads.getB2(), 0.4128015980961886, Epsilon);

}

TEST(DigitalFiltersTEST, TEST_Notch)
{
    using namespace DigitalFilters;

    BicuadCoefficients bicuads;

    bicuads = IIRFilters::Notch(100, 10, 1000);


    ASSERT_NEAR(bicuads.getA0(), 0.9714498065192796, Epsilon);
    ASSERT_NEAR(bicuads.getA1(), -1.5718388053127037, Epsilon);
    ASSERT_NEAR(bicuads.getA2(), 0.9714498065192796, Epsilon);

    ASSERT_NEAR(bicuads.getB1(), -1.5718388053127037, Epsilon);
    ASSERT_NEAR(bicuads.getB2(), 0.9428996130385592, Epsilon);

}

TEST(DigitalFiltersTEST, TEST_OnePoleHighPass)
{
    using namespace DigitalFilters;

    BicuadCoefficients bicuads;

    bicuads = IIRFilters::OnePoleHighPass(100, 1000);


    ASSERT_NEAR(bicuads.getA0(), 0.9189974078420569, Epsilon);

    ASSERT_NEAR(bicuads.getA1(), 0, Epsilon);

    ASSERT_NEAR(bicuads.getA2(), 0, Epsilon);

    ASSERT_NEAR(bicuads.getB1(), 0.08100259215794314, Epsilon);

    ASSERT_NEAR(bicuads.getB2(), 0, Epsilon);

}


TEST(DigitalFiltersTEST, Test_OnePoleLowPass)
{
    using namespace DigitalFilters;

    BicuadCoefficients bicuads;

    bicuads = IIRFilters::OnePoleLowPass(100, 1000);

    ASSERT_NEAR(bicuads.getA0(), 0.4665119089088967, Epsilon);

    ASSERT_NEAR(bicuads.getA1(), 0, Epsilon);

    ASSERT_NEAR(bicuads.getA2(), 0, Epsilon);

    ASSERT_NEAR(bicuads.getB1(), -0.5334880910911033, Epsilon);

    ASSERT_NEAR(bicuads.getB2(), 0, Epsilon);

}

TEST(DigitalFiltersTEST, Test_PeakEq)
{
    using namespace DigitalFilters;

    BicuadCoefficients bicuads;

    bicuads = IIRFilters::PeakEq(5, 100, 10, 1000);


    ASSERT_NEAR(bicuads.getA0(), 1.0222200277386724, Epsilon);

    ASSERT_NEAR(bicuads.getA1(), -1.5718388053127037, Epsilon);

    ASSERT_NEAR(bicuads.getA2(), 0.920679585299887, Epsilon);

    ASSERT_NEAR(bicuads.getB1(), -1.5718388053127037, Epsilon);

    ASSERT_NEAR(bicuads.getB2(), 0.9428996130385592, Epsilon);

}


TEST(DigitalFiltersTEST, Test_EvalBicuad)
{
    using namespace DigitalFilters;

    // Define your test input values
    long double fc = 110.0;  // Example frequency
    long double fs = 1000.0;  // Example sample rate

    long double zeros[3] =
    {
        1.0222200277386724,
        -1.5718388053127037,
        0.920679585299887,
    };

    long double poles[3] =
    {
        (1.0),
        -1.5718388053127037,
        0.9428996130385592,
    };

    long double w , magnitude_db, phase;

    std::complex<long double> res;

    w = FilterUtils<long double>::HzToW (110.0) / fs;

    res = FilterEvaluator<long double>::EvalBicuad(
      zeros[0], zeros[1], zeros[2], poles[1], poles[2], w);

    magnitude_db = FilterUtils<long double>::GainTodB(abs(res));
    phase = arg(res);


    ASSERT_NEAR(magnitude_db, 1.5041110035372895, Epsilon);
    ASSERT_NEAR(phase, -2.604320565152820e-01, Epsilon);


    w = FilterUtils<long double>::HzToW (90.0) / fs;

    res = FilterEvaluator<long double>::EvalBicuad(
      zeros[0], zeros[1], zeros[2], poles[1], poles[2], w);

    magnitude_db = FilterUtils<long double>::GainTodB(abs(res));
    phase = arg(res);


    ASSERT_NEAR(magnitude_db, 1.3312607813937896, Epsilon);

    ASSERT_NEAR(phase, 2.509964622124102e-01, Epsilon);


    w = FilterUtils<long double>::HzToW (100.0) / fs;

    res =
      FilterEvaluator<long double>::EvalBicuad(
      zeros[0], zeros[1], zeros[2], poles[1], poles[2], w);

    magnitude_db = FilterUtils<long double>::GainTodB(abs(res));
    phase = arg(res);


    ASSERT_NEAR(magnitude_db, 5, Epsilon);


    BicuadCoefficients bicuads;

    bicuads = IIRFilters::PeakEq(5, 100, 10, 1000);


    w = FilterUtils<long double>::HzToW (100.0) / fs;

    res =
      FilterEvaluator<long double>::EvalBicuad(
      bicuads.getA0(), bicuads.getA1(), bicuads.getA2(),
      bicuads.getB1(), bicuads.getB2(), w);

    magnitude_db = FilterUtils<long double>::GainTodB(abs(res));
    phase = arg(res);


    ASSERT_NEAR(magnitude_db, 5, Epsilon);

}

//// Define a test case
TEST(DigitalFiltersTEST, Test_EvalBicuadTrig)
{
  using namespace DigitalFilters;

  // Define your test input values
  long double fc = 110.0;  // Example frequency
  long double fs = 1000.0;  // Example sample rate

  long double zeros[3] =
  {
      1.0222200277386724,
      -1.5718388053127037,
      0.920679585299887,
  };

  long double poles[3] =
  {
      (1.0),
      -1.5718388053127037,
      0.9428996130385592,
  };

  long double w, magnitude_db, phase;

  std::pair<long double, long double> res;

  w = FilterUtils<long double>::HzToW (110.0) / fs;

  res = FilterEvaluator<long double>::EvalBicuadTrig(
    zeros[0], zeros[1], zeros[2], poles[1], poles[2], w);

  magnitude_db = FilterUtils<long double>::GainTodB(res.first);
  phase = res.second;


  ASSERT_NEAR(magnitude_db, 1.5041110035372895, Epsilon);
  ASSERT_NEAR(phase, -2.604320565152820e-01, Epsilon);


  w = FilterUtils<long double>::HzToW (90.0) / fs;

  res = FilterEvaluator<long double>::EvalBicuadTrig(
    zeros[0], zeros[1], zeros[2], poles[1], poles[2], w);

  magnitude_db = FilterUtils<long double>::GainTodB(res.first);
  phase = res.second;


  ASSERT_NEAR(magnitude_db, 1.3312607813937896, Epsilon);

  ASSERT_NEAR(phase, 2.509964622124102e-01, Epsilon);


  w = FilterUtils<long double>::HzToW (100.0) / fs;

  res =
    FilterEvaluator<long double>::EvalBicuadTrig(
    zeros[0], zeros[1], zeros[2], poles[1], poles[2], w);

  magnitude_db = FilterUtils<long double>::GainTodB(res.first);
  phase = res.second;

  ASSERT_NEAR(magnitude_db, 5, Epsilon);


  BicuadCoefficients bicuads;

  bicuads = IIRFilters::PeakEq(5, 100, 10, 1000);


  w = FilterUtils<long double>::HzToW (100.0) / fs;

  res =
    FilterEvaluator<long double>::EvalBicuadTrig(
    bicuads.getA0(), bicuads.getA1(), bicuads.getA2(),
    bicuads.getB1(), bicuads.getB2(), w);

  magnitude_db = FilterUtils<long double>::GainTodB(res.first);
  phase = res.second;


  ASSERT_NEAR(magnitude_db, 5, Epsilon);

}

//// Define a test case
TEST(DigitalFiltersTEST, Test_FrequencyResponseTrig)
{
    using namespace DigitalFilters;

    // Define your test input values
    long double fc = 110.0;  // Example frequency
    long double fs = 1000.0;  // Example sample rate

    long double zeros[3] =
    {
        1.0222200277386724,
        -1.5718388053127037,
        0.920679585299887,
    };

    long double poles[3] =
    {
        (1.0),
        -1.5718388053127037,
        0.9428996130385592,
    };

    long double pi = 2 * acos(0.0);

    long double w = 2 * pi * fc / fs;

    long double magnitude_db, phase;

    std::pair<long double, long double> res = FilterEvaluator<long double>
        ::FrequencyResponseTrig(zeros, poles, 3, w);

    magnitude_db = 20L * log10(abs(res.first));
    phase = res.second;


    ASSERT_NEAR(magnitude_db, 1.5041110035372895, Epsilon);

    ASSERT_NEAR(phase, -2.604320565152820e-01, Epsilon);

    w =  2 * pi * 90 / fs;

    res = FilterEvaluator<long double>
        ::FrequencyResponseTrig(zeros, poles, 3, w);

    magnitude_db = 20L * log10(abs(res.first));
    phase = res.second;

    ASSERT_NEAR(magnitude_db, 1.3312607813937896, Epsilon);

    ASSERT_NEAR(phase, 2.509964622124102e-01, Epsilon);
}


TEST(DigitalFiltersTEST, Test_FrequencyResponse)
{
    using namespace DigitalFilters;

    // Define your test input values
    long double fc = 110.0;  // Example frequency
    long double fs = 1000.0;  // Example sample rate

    long double zeros[3] =
    {
        1.0222200277386724,
        -1.5718388053127037,
        0.920679585299887,
    };

    long double poles[3] =
    {
        (1.0),
        -1.5718388053127037,
        0.9428996130385592,
    };

    long double pi = 2 * acos(0.0);

    long double w = 2 * pi * fc / fs;

    long double magnitude_db, phase;

    std::complex<long double> res = FilterEvaluator<long double>
                                ::FrequencyResponse(zeros, poles, 3, w);

    magnitude_db = 20L * log10(abs(res));
    phase = arg(res);


    ASSERT_NEAR(magnitude_db, 1.5041110035372895, Epsilon);

    ASSERT_NEAR(phase, -2.604320565152820e-01, Epsilon);

    w = FilterUtils<long double>::HzToW (90) / fs;

    res = FilterEvaluator<long double>
        ::FrequencyResponse(zeros, poles, 3, w);

    magnitude_db = FilterUtils<long double>::GainTodB(abs(res));
    phase = arg(res);


    ASSERT_NEAR(magnitude_db, 1.3312607813937896, Epsilon);

    ASSERT_NEAR(phase, 2.509964622124102e-01, Epsilon);

}


TEST(DigitalFiltersTEST, TEST_Parallel)
{
  BicuadCoefficients bicuads;

  bicuads = IIRFilters::PeakEq(5, 100, 10, 1000);


  auto start = std::chrono::high_resolution_clock::now();


  auto res = IIRfreqResponse::FrequencyResponse(bicuads.GetZeros(),
    bicuads.GetPoles(),
    randomSet,
    1000);


  auto end = std::chrono::high_resolution_clock::now();


  auto duration =
    std::chrono::duration_cast<std::chrono::microseconds>(end - start);


  std::cout << "Exec Time: " << duration.count()/1000
    << " miliseconds" << std::endl;

  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}


TEST(DigitalFiltersTEST, Test_Size)
{
    int integerType;
    char charType;
    float floatType;
    double doubleType;
    long double longDoubleType;

    // Calculate and Print
    // the size of integer type
    std::cout << "Size of int is: " << sizeof(integerType)
        << "\n";

    // Calculate and Print
    // the size of doubleType
    std::cout << "Size of char is: " << sizeof(charType) << "\n";

    // Calculate and Print
    // the size of charType
    std::cout << "Size of float is: " << sizeof(floatType)
        << "\n";

    // Calculate and Print
    // the size of floatType
    std::cout << "Size of double is: " << sizeof(doubleType)
        << "\n";

    std::cout << "Size of double is: " << sizeof(longDoubleType)
        << "\n";

    typedef union
    {
      long long i64;
      double d64;
    } dbl_64;

    double value  = 5;

      dbl_64 s;
      s.d64 = value;
      s.i64++;
      double  res =  s.d64 - value;

      std::cout << "Machine Epsilon is: " << res
        << "\n";

    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);

}