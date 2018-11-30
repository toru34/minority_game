#include "passive_strategy.h"

PassiveStrategy::PassiveStrategy(const float eps)
{
    this->eps = eps;
    this->score = 0;
}

float PassiveStrategy::get_score()
{
    return this->score;
}

int PassiveStrategy::choose_action(const int history_integer)
{
    return STAY;
}

void PassiveStrategy::update_score(const int history_integer, const int excess_demand)
{
    this->score += this->eps;
}