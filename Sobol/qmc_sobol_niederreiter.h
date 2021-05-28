#pragma once

constexpr int QRNG_DIMENSIONS = 11;
constexpr int QRNG_RESOLUTION = 31;
constexpr float INT_SCALE     = 1.0F / (float)(0x80000001U);

typedef long long int INT64;

extern "C" void initQuasirandomGenerator(unsigned int table[QRNG_DIMENSIONS][QRNG_RESOLUTION]);

float rndQmcSobolN(unsigned int pos, int dim, const unsigned int *c_Table);
