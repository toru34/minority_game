#ifndef CONFIG_H_
#define CONFIG_H_

#include <random>

extern const int BUY;
extern const int STAY;
extern const int SELL;

extern const int WIN;
extern const int EVEN;
extern const int LOSE;

extern const float INF;

extern std::mt19937 RNG;
extern std::default_random_engine ENGINE;
extern std::uniform_real_distribution<float> RNG_UNIFORM;

#endif