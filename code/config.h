#ifndef CONFIG_H_
#define CONFIG_H_

#include <random>

extern const int N_MINORITY_AGENTS;
extern const int N_PRODUCER_AGENTS;
extern const int N_SPECULATOR_AGENTS;

extern const int N_AGENTS;

extern const float EPS;

extern const int N_ITERS;
extern const int N_RUNS;

extern const int BUY;
extern const int STAY;
extern const int SELL;

extern const int WIN;
extern const int EVEN;
extern const int LOSE;

extern const int S;
extern const int P;

extern const float INF;

extern std::mt19937 rng;
extern std::default_random_engine engine;
extern std::uniform_int_distribution<int> rng_integer;
extern std::uniform_int_distribution<int> rng_history_integer;
extern std::uniform_real_distribution<float> rng_uniform;

#endif