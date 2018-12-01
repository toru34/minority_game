#include "config.h"

const int N_MINORITY_AGENTS = 101;
const int N_PRODUCER_AGENTS = 0;
const int N_SPECULATOR_AGENTS = 0;

const int N_AGENTS = N_MINORITY_AGENTS + N_PRODUCER_AGENTS + N_SPECULATOR_AGENTS;

const float EPS = 0.01;

const int N_ITERS = 10000;
const int N_RUNS = 4;

const int BUY = 1;
const int STAY = 0;
const int SELL = -1;

const int WIN = 1;
const int EVEN = 0;
const int LOSE = -1;

const int S = 2;
const int P = 16;

const float INF = 1001001001;

std::mt19937 rng(34);
std::default_random_engine engine(34);
std::uniform_int_distribution<int> rng_nagents_integer(- N_AGENTS, N_AGENTS);
std::uniform_int_distribution<int> rng_history_integer(0, P - 1); // x ~ {0, 1, ..., P - 1}
std::uniform_real_distribution<float> rng_uniform(0.0, 1.0); // x ~ [0, 1)