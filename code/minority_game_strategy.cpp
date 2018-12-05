#include "minority_game_strategy.h"

MinorityGameStrategy::MinorityGameStrategy(const int p)
{
    this->p = p;
    this->score = 0;
    for (unsigned int i = 0; i < p; ++i) {
        this->actions.emplace_back(RNG_UNIFORM(ENGINE) < 0.5 ? BUY : SELL);
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