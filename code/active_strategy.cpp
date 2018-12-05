#include "active_strategy.h"

ActiveStrategy::ActiveStrategy(const int p)
{
    this->score = 0;
    for (unsigned int i = 0; i < p; ++i) {
        this->actions.emplace_back(RNG_UNIFORM(ENGINE) < 0.5 ? BUY : SELL);
    }
}

float ActiveStrategy::get_score()
{
    return this->score;
}

int ActiveStrategy::choose_action(const int history_integer)
{
    return this->actions.at(history_integer);
}

void ActiveStrategy::update_score(const int history_integer, const int excess_demand)
{
    this->score -= this->actions.at(history_integer) * excess_demand;
}