#include "Sampling.h"

////////////////////////////////////////////////////////////////////////


Sampling::Sampling(SamplingMethod& sm) :
  m_sampMeth(sm)
{
  // Sobol
  initQuasirandomGenerator(m_sobolTable);
}


float Sampling::GetOneRndDigit(const uint32_t a_sobolPos, const int a_SobolDim) const
{
  switch (m_sampMeth)
  {
  case SamplingMethod::UNIFORM:    return Simple1D();
  case SamplingMethod::STRATIFIED: return Stratified(10);
  case SamplingMethod::SOBOL:      return rndQmcSobolN(a_sobolPos, a_SobolDim, &m_sobolTable[0][0]);
  default:
    break;
  }
  return 0.0f;
}



float Sampling::Simple1D() const
{
  return (float)(rand() % RAND_MAX) / (float)RAND_MAX;
}

//////////////////////////
// hammersley 2d
//////////////////////////

//float radicalInverse_VdC(unsigned bits)
//{
//  bits = (bits << 16u) | (bits >> 16u);
//  bits = ((bits & 0x55555555u) << 1u) | ((bits & 0xAAAAAAAAu) >> 1u);
//  bits = ((bits & 0x33333333u) << 2u) | ((bits & 0xCCCCCCCCu) >> 2u);
//  bits = ((bits & 0x0F0F0F0Fu) << 4u) | ((bits & 0xF0F0F0F0u) >> 4u);
//  bits = ((bits & 0x00FF00FFu) << 8u) | ((bits & 0xFF00FF00u) >> 8u);
//  return float(float(bits) * 2.3283064365386963e-10); // / 0x100000000
//}
//
//vec2 Hammersley2D(unsigned i, unsigned N) 
//{
//  return vec2(float(i) / float(N), radicalInverse_VdC(i));
//}



//////////////////////////
// Stratified MC
////////////////////////// 

float RandCell(const uint32_t numCell)
{
  return (rand() % numCell) / (float)numCell;
}


void RandomCellArray(std::vector<float>& a_array)
{
  const auto sizeArray = a_array.size();

  for (int i = 0; i < sizeArray; i++)
  {
    const int numCell1 = rand() % sizeArray;
    const int numCell2 = rand() % sizeArray;
    const float a      = a_array[numCell1];
    const float b      = a_array[numCell2];
    a_array[numCell1]  = b;
    a_array[numCell2]  = a;
  }
}


float Sampling::Stratified(const uint32_t a_numStrat) const
{
  const float strat = RandCell(a_numStrat);  
  return strat + Simple1D() / (float)(a_numStrat);
}



