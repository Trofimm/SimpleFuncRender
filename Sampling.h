#pragma once
#include "Math.h"
#include "../Sobol/qmc_sobol_niederreiter.h"

////////////////////////////////////////////////////////////////////////


enum class SamplingMethod { UNIFORM, STRATIFIED, SOBOL };

struct Sampling
{
  explicit Sampling(SamplingMethod& sm);

  float GetOneRndDigit(const uint32_t a_sobolPos, const int a_SobolDim) const;

  float Simple1D() const;
  float Stratified(const uint32_t a_numStrat) const;

private:
  SamplingMethod& m_sampMeth;
  uint32_t m_sobolTable[QRNG_DIMENSIONS][QRNG_RESOLUTION];
};


