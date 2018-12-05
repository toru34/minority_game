#include "config.h"

const int BUY = 1;
const int STAY = 0;
const int SELL = -1;

const int WIN = 1;
const int EVEN = 0;
const int LOSE = -1;

const float INF = 1001001001;

std::mt19937 RNG(34);
std::default_random_engine ENGINE(34);
std::uniform_real_distribution<float> RNG_UNIFORM(0.0, 1.0); // x ~ [0, 1)