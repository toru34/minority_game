#include "minority_game_strategy.h"

MinorityGameStrategy::MinorityGameStrategy(const int p, bool is_hetero)
{
    this->p = p;
    this->score = 0;

    if (is_hetero) {
        std::uniform_int_distribution<int> rng_history_integer(0, this->p);
        int k = rng_history_integer(ENGINE); // k ~ {0, 1, 2, ..., P}
        for (unsigned int i = 0; i < p; ++i) {
            this->actions.emplace_back(RNG_UNIFORM(ENGINE) < (k / static_cast<float>(this->p)) ? BUY : SELL);
        }

    } else {
        for (unsigned int i = 0; i < p; ++i) {
            this->actions.emplace_back(RNG_UNIFORM(ENGINE) < 0.5 ? BUY : SELL);
        }
    }
}

float MinorityGameStrategy::get_score()
{
    return this->score;
}

int MinorityGameStrategy::choose_action(const int history_integer)
{
    return this->actions.at(history_integer);
}

void MinorityGameStrategy::update_score(const int history_integer, const int excess_demand)
{
    if (excess_demand > 0) {
        this->score += this->actions.at(history_integer) == BUY ? -1 : 1;
    } else {
        this->score += this->actions.at(history_integer) == BUY ? 1 : -1;
    }
}