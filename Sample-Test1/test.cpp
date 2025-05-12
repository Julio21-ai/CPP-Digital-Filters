#include "pch.h"
#include <math.h>
#include <iostream>
#include <complex>
#include "..\include\DigitalFilters.h"
#include <random>
#include <chrono>
#include "..\include\IIRDesign.h"
#include "..\include\Utils.h"
#include "..\include\Evaluator.h"
#include "..\DigitalFiltersLib\IIRfreqResponse.h"

using namespace DigitalFilters;
using namespace DigitalFilters::Utils;
using namespace DigitalFilters::Eval;
using BiquadCoefficientsd = Biquad<double>;

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

  std::vector<double> randomSet = generateRandomFloats(448000000);

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(DigitalFiltersTEST, TEST_LowShelf1stOrder)
{
    using namespace DigitalFilters;

    BiquadCoefficientsd bicuads;

    bicuads = IIR::LowShelf1stOrder(5.0, 100.0, 1000.0);

    ASSERT_NEAR(bicuads.a0, 1.1908631219032908, Epsilon);
    ASSERT_NEAR(bicuads.a1, -0.31866232759113794, Epsilon);
    ASSERT_NEAR(bicuads.a2, 0, Epsilon);

    ASSERT_NEAR(bicuads.b1, -0.5095254494944288, Epsilon);
    ASSERT_NEAR(bicuads.b2, 0, Epsilon);

}

TEST(DigitalFiltersTEST, TEST_HighShelf1stOrder)
{
    using namespace DigitalFilters;

    BiquadCoefficientsd bicuads;

    bicuads = IIR::HighShelf1stOrder(5.0, 100.0, 1000.0);

    ASSERT_NEAR(bicuads.a0, 1.587416288135632,Epsilon);
    ASSERT_NEAR(bicuads.a1, -1.0969417376300605, Epsilon);
    ASSERT_NEAR(bicuads.a2, 0, Epsilon);

    ASSERT_NEAR(bicuads.b1, -0.5095254494944288, Epsilon);
    ASSERT_NEAR(bicuads.b2, 0, Epsilon);

}

TEST(DigitalFiltersTEST, TEST_HighPass1stOrder)
{
    using namespace DigitalFilters;

    BiquadCoefficientsd bicuads;

    bicuads = IIR::HighPass1stOrder(100.0, 1000.0);

    ASSERT_NEAR(bicuads.a0, 0.7547627247472144, Epsilon);
    ASSERT_NEAR(bicuads.a1, -0.7547627247472144, Epsilon);
    ASSERT_NEAR(bicuads.a2, 0, Epsilon);

    ASSERT_NEAR(bicuads.b1, -0.5095254494944288, Epsilon);
    ASSERT_NEAR(bicuads.b2, 0, Epsilon);

}

TEST(DigitalFiltersTEST, TEST_LowPass1stOrder)
{
    using namespace DigitalFilters;

    BiquadCoefficientsd bicuads;

    bicuads = IIR::LowPass1stOrder( 100.0, 1000.0);

    ASSERT_NEAR(bicuads.a0, 0.24523727525278555, Epsilon);
    ASSERT_NEAR(bicuads.a1, 0.24523727525278555, Epsilon);
    ASSERT_NEAR(bicuads.a2, 0, Epsilon);

    ASSERT_NEAR(bicuads.b1, -0.5095254494944289, Epsilon);
    ASSERT_NEAR(bicuads.b2, 0, Epsilon);

}

TEST(DigitalFiltersTEST, TEST_AllPass)
{
    using namespace DigitalFilters;

    BiquadCoefficientsd bicuads;

    bicuads = IIR::AllPass1stOrder( 100.0, 1000.0);

    ASSERT_NEAR(bicuads.a0, 0.5095254494944288, Epsilon);
    ASSERT_NEAR(bicuads.a1, -1, Epsilon);
    ASSERT_NEAR(bicuads.a2, 0, Epsilon);

    ASSERT_NEAR(bicuads.b1, -0.5095254494944288, Epsilon);
    ASSERT_NEAR(bicuads.b2, 0, Epsilon);

}


TEST(DigitalFiltersTEST, TEST_AllPassQ)
{
    using namespace DigitalFilters;

    BiquadCoefficientsd bicuads;

    bicuads = IIR::AllPassQ(100.0, 10.0, 1000.0);

    ASSERT_NEAR(bicuads.a0, 0.9428996130385592 , Epsilon);
    ASSERT_NEAR(bicuads.a1, -1.5718388053127037, Epsilon);
    ASSERT_NEAR(bicuads.a2, 1                  , Epsilon);

    ASSERT_NEAR(bicuads.b1, -1.5718388053127037, Epsilon);
    ASSERT_NEAR(bicuads.b2, 0.9428996130385592, Epsilon);

}



TEST(DigitalFiltersTEST, TEST_BandPass)
{
    using namespace DigitalFilters;

    BiquadCoefficientsd bicuads;

    bicuads = IIR::BandPass(100.0, 10.0, 1000.0);

    ASSERT_NEAR(bicuads.a0, 0.028550193480720448, Epsilon);
    ASSERT_NEAR(bicuads.a1, 0, Epsilon);
    ASSERT_NEAR(bicuads.a2, -0.028550193480720448, Epsilon);

    ASSERT_NEAR(bicuads.b1, -1.5718388053127037, Epsilon);
    ASSERT_NEAR(bicuads.b2, 0.9428996130385592, Epsilon);

}



TEST(DigitalFiltersTEST, TEST_HighPass)
{
    using namespace DigitalFilters;

    BiquadCoefficientsd bicuads;

    bicuads = IIR::HighPass( 100.0,10.0 , 1000.0);

    ASSERT_NEAR(bicuads.a0, 0.8786846045878157, Epsilon);
    ASSERT_NEAR(bicuads.a1, -1.7573692091756314, Epsilon);
    ASSERT_NEAR(bicuads.a2, 0.8786846045878157, Epsilon);

    ASSERT_NEAR(bicuads.b1, -1.5718388053127037, Epsilon);
    ASSERT_NEAR(bicuads.b2, 0.9428996130385592, Epsilon);

}


TEST(DigitalFiltersTEST, TEST_HighShelf)
{
    using namespace DigitalFilters;

    BiquadCoefficientsd bicuads;

    bicuads = IIR::HighShelf(5.0, 100.0,  1000.0);

    ASSERT_NEAR(bicuads.a0, 1.595199772351261, Epsilon);
    ASSERT_NEAR(bicuads.a1, -2.1375367952754485, Epsilon);
    ASSERT_NEAR(bicuads.a2, 0.8121581184804753, Epsilon);

    ASSERT_NEAR(bicuads.b1, -1.1429805025399011, Epsilon);
    ASSERT_NEAR(bicuads.b2, 0.4128015980961886, Epsilon);

}


TEST(DigitalFiltersTEST, TEST_HighShelfQ)
{
    using namespace DigitalFilters;

    BiquadCoefficientsd bicuads;

    bicuads = IIR::HighShelfQ( 5.0, 100.0, 1 / sqrt( 2.0 ), 1000.0 );

    ASSERT_NEAR(bicuads.a0, 1.595199772351261, Epsilon);
    ASSERT_NEAR(bicuads.a1, -2.1375367952754485, Epsilon);
    ASSERT_NEAR(bicuads.a2, 0.8121581184804753, Epsilon);

    ASSERT_NEAR(bicuads.b1, -1.1429805025399011, Epsilon);
    ASSERT_NEAR(bicuads.b2, 0.4128015980961886, Epsilon);

}


TEST(DigitalFiltersTEST, TEST_LowShelf)
{
    using namespace DigitalFilters;

    BiquadCoefficientsd bicuads;

    bicuads = IIR::LowShelf(5.0, 100.0,  1000.0);

    ASSERT_NEAR(bicuads.a0, 1.1504206767498881, Epsilon);
    ASSERT_NEAR(bicuads.a1, -1.0379824010070995, Epsilon);
    ASSERT_NEAR(bicuads.a2, 0.3673790228791024, Epsilon);

    ASSERT_NEAR(bicuads.b1, -1.1429805025399011, Epsilon);
    ASSERT_NEAR(bicuads.b2, 0.4128015980961886, Epsilon);

}

TEST(DigitalFiltersTEST, TEST_LowShelfQ)
{
    using namespace DigitalFilters;

    BiquadCoefficientsd bicuads;

    bicuads = IIR::LowShelfQ(5.0, 100.0, 1 / sqrt(2.0), 1000.0);


    ASSERT_NEAR(bicuads.a0, 1.1504206767498881, Epsilon);
    ASSERT_NEAR(bicuads.a1, -1.0379824010070995, Epsilon);
    ASSERT_NEAR(bicuads.a2, 0.3673790228791024, Epsilon);

    ASSERT_NEAR(bicuads.b1, -1.1429805025399011, Epsilon);
    ASSERT_NEAR(bicuads.b2, 0.4128015980961886, Epsilon);

}

TEST(DigitalFiltersTEST, TEST_Notch)
{
    using namespace DigitalFilters;

    BiquadCoefficientsd bicuads;

    bicuads = IIR::Notch(100.0, 10.0, 1000.0);


    ASSERT_NEAR(bicuads.a0, 0.9714498065192796, Epsilon);
    ASSERT_NEAR(bicuads.a1, -1.5718388053127037, Epsilon);
    ASSERT_NEAR(bicuads.a2, 0.9714498065192796, Epsilon);

    ASSERT_NEAR(bicuads.b1, -1.5718388053127037, Epsilon);
    ASSERT_NEAR(bicuads.b2, 0.9428996130385592, Epsilon);

}

TEST(DigitalFiltersTEST, TEST_OnePoleHighPass)
{
    using namespace DigitalFilters;

    BiquadCoefficientsd bicuads;

    bicuads = IIR::OnePoleHighPass(100.0, 1000.0);


    ASSERT_NEAR(bicuads.a0, 0.9189974078420569, Epsilon);

    ASSERT_NEAR(bicuads.a1, 0, Epsilon);

    ASSERT_NEAR(bicuads.a2, 0, Epsilon);

    ASSERT_NEAR(bicuads.b1, 0.08100259215794314, Epsilon);

    ASSERT_NEAR(bicuads.b2, 0, Epsilon);

}


TEST(DigitalFiltersTEST, Test_OnePoleLowPass)
{
    using namespace DigitalFilters;

    BiquadCoefficientsd bicuads;

    bicuads = IIR::OnePoleLowPass(100.0, 1000.0);

    ASSERT_NEAR(bicuads.a0, 0.4665119089088967, Epsilon);

    ASSERT_NEAR(bicuads.a1, 0, Epsilon);

    ASSERT_NEAR(bicuads.a2, 0, Epsilon);

    ASSERT_NEAR(bicuads.b1, -0.5334880910911033, Epsilon);

    ASSERT_NEAR(bicuads.b2, 0, Epsilon);

}

TEST(DigitalFiltersTEST, Test_PeakEq)
{
    using namespace DigitalFilters;

    BiquadCoefficientsd bicuads;

    bicuads = IIR::PeakEq(5.0, 100.0, 10.0, 1000.0);


    ASSERT_NEAR(bicuads.a0, 1.0222200277386724, Epsilon);

    ASSERT_NEAR(bicuads.a1, -1.5718388053127037, Epsilon);

    ASSERT_NEAR(bicuads.a2, 0.920679585299887, Epsilon);

    ASSERT_NEAR(bicuads.b1, -1.5718388053127037, Epsilon);

    ASSERT_NEAR(bicuads.b2, 0.9428996130385592, Epsilon);

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

    w = DigitalFilters::Utils::HzToOmega (110.0) / fs;

    res = Eval::CalcFreqResponse( Biquad(
      zeros[0], zeros[1], zeros[2], poles[1], poles[2]), w);

    magnitude_db = Utils::GainTodB(abs(res));
    phase = arg(res);


    ASSERT_NEAR(magnitude_db, 1.5041110035372895, Epsilon);
    ASSERT_NEAR(phase, -2.604320565152820e-01, Epsilon);


    w = Utils::HzToOmega (90.0) / fs;

    res = Eval::CalcFreqResponse( Biquad(
      zeros[0], zeros[1], zeros[2], poles[1], poles[2]), w);

    magnitude_db = Utils::GainTodB(abs(res));
    phase = arg(res);


    ASSERT_NEAR(magnitude_db, 1.3312607813937896, Epsilon);

    ASSERT_NEAR(phase, 2.509964622124102e-01, Epsilon);


    w = Utils::HzToOmega (100.0) / fs;

    res =
      Eval::CalcFreqResponse( Biquad(
      zeros[0], zeros[1], zeros[2], poles[1], poles[2]), w);

    magnitude_db = Utils::GainTodB(abs(res));
    phase = arg(res);


    ASSERT_NEAR(magnitude_db, 5, Epsilon);


    auto bicuads = IIR::PeakEq(5.0l, 100.0l, 10.0l, 1000.0l);


    w = Utils::HzToOmega (100.0) / fs;

    res =
      Eval::CalcFreqResponse( bicuads, w);

    magnitude_db = Utils::GainTodB(abs(res));
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

  FrequencyResponse<long double> res;

  w = Utils::HzToOmega (110.0) / fs;

  res = Eval::CalcFreqResponseTrig( Biquad(
    zeros[0], zeros[1], zeros[2], poles[1], poles[2]), w);

  magnitude_db = 20L * log10( abs( res.magnitude ) );
  phase = res.phase;


  ASSERT_NEAR(magnitude_db, 1.5041110035372895, Epsilon);
  ASSERT_NEAR(phase, -2.604320565152820e-01, Epsilon );


  w = Utils::HzToOmega (90.0) / fs;

  res = Eval::CalcFreqResponseTrig( Biquad(
    zeros[0], zeros[1], zeros[2], poles[1], poles[2]), w);

  magnitude_db = 20L * log10( abs( res.magnitude ) );
  phase = res.phase;


  ASSERT_NEAR(magnitude_db, 1.3312607813937896, Epsilon);

  ASSERT_NEAR(phase, 2.509964622124102e-01, Epsilon);


  w = Utils::HzToOmega (100.0) / fs;

  res =
    Eval::CalcFreqResponseTrig( Biquad(
    zeros[0], zeros[1], zeros[2], poles[1], poles[2]), w);

  magnitude_db = 20L * log10( abs( res.magnitude ) );
  phase = res.phase;

  ASSERT_NEAR(magnitude_db, 5, Epsilon);



  auto bicuads = IIR::PeakEq(5.0l, 100.0l, 10.0l, 1000.0l);


  w = Utils::HzToOmega (100.0) / fs;

  res =
    Eval::CalcFreqResponseTrig(Biquad(
    bicuads.a0, bicuads.a1, bicuads.a2,
    bicuads.b1, bicuads.b2), w);

  magnitude_db = 20L * log10( abs( res.magnitude ) );
  phase = res.phase;


  ASSERT_NEAR(magnitude_db, 5, Epsilon);

}

//// Define a test case
TEST(DigitalFiltersTEST, Test_FrequencyResponseTrig)
{
    using namespace DigitalFilters;

    // Define your test input values
    long double fc = 110.0;  // Example frequency
    long double fs = 1000.0;  // Example sample rate

    const long double zeros[3] =
    {
        1.0222200277386724,
        -1.5718388053127037,
        0.920679585299887,
    };

    const long double poles[3] =
    {
        (1.0),
        -1.5718388053127037,
        0.9428996130385592,
    };

    long double pi = 2 * acos(0.0);

    long double w = 2 * pi * fc / fs;

    long double magnitude_db, phase;

    auto res_trig = Eval::CalcFreqResponseTrig<long double>(zeros, poles, w);

    auto magnitude_trig_db = 20L * log10(abs( res_trig.magnitude));
    auto phase_trig = res_trig.phase;

    std::span mySpan1( zeros );
    std::span mySpan2( poles );

    auto res = Eval::CalcFreqResponse<long double >( mySpan1, mySpan2, w );

    magnitude_db = Utils::GainTodB( abs( res ) );
    phase = arg( res );



    ASSERT_NEAR(magnitude_db, 1.5041110035372895, Epsilon);

    ASSERT_NEAR(phase, -2.604320565152820e-01, Epsilon);

    w =  2 * pi * 90 / fs;

    res_trig = Eval::CalcFreqResponseTrig<long double >( mySpan1, mySpan2, w);

    magnitude_trig_db = 20L * log10(abs( res_trig.magnitude ));
    phase_trig = res_trig.phase;

    ASSERT_NEAR( magnitude_trig_db, 1.3312607813937896, Epsilon);

    ASSERT_NEAR( phase_trig, 2.509964622124102e-01, Epsilon);
}


TEST(DigitalFiltersTEST, Test_FrequencyResponse)
{
    using namespace DigitalFilters;

    // Define your test input values
    long double fc = 110.0;  // Example frequency
    long double fs = 1000.0;  // Example sample rate

    const long double zeros[3] =
    {
        1.0222200277386724,
        -1.5718388053127037,
        0.920679585299887,
    };

    const long double poles[3] =
    {
        (1.0),
        -1.5718388053127037,
        0.9428996130385592,
    };

    long double pi = 2 * acos(0.0);

    long double w = 2 * pi * fc / fs;

    long double magnitude_db, phase;

    std::span mySpan1{ zeros };
    std::span mySpan2{ poles };

    std::complex<long double> res = Eval::CalcFreqResponse<long double >( mySpan1, mySpan2, w);

    magnitude_db = 20L * log10(abs(res));
    phase = arg(res);


    ASSERT_NEAR(magnitude_db, 1.5041110035372895, Epsilon);

    ASSERT_NEAR(phase, -2.604320565152820e-01, Epsilon);

    w = Utils::HzToOmega (90.0l) / fs;

    res = Eval::CalcFreqResponse<long double >(zeros, poles,  w);

    magnitude_db = Utils::GainTodB(abs(res));
    phase = arg(res);


    ASSERT_NEAR(magnitude_db, 1.3312607813937896, Epsilon);

    ASSERT_NEAR(phase, 2.509964622124102e-01, Epsilon);

}


TEST(DigitalFiltersTEST, TEST_Parallel)
{
  BiquadCoefficientsd bicuads;

  bicuads = IIR::PeakEq(5.0, 100.0, 10.0, 1000.0);


  auto start = std::chrono::high_resolution_clock::now();


  auto res = IIRfreqResponse::FrequencyResponse(bicuads.GetDenominatorCoefficients(),
    bicuads.GetNumeratorCoefficients(),
    randomSet,
    1000.0);


  auto end = std::chrono::high_resolution_clock::now();


  auto duration =
    std::chrono::duration_cast<std::chrono::microseconds>(end - start);


  std::cout << "Exec Time: " << duration.count()/1000
    << " milliseconds" << std::endl;

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