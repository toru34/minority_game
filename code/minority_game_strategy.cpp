#include "minority_game_strategy.h"

// MinorityGameStrategy::MinorityGameStrategy(const int m)
MinorityGameStrategy::MinorityGameStrategy(const int p)
{
    // this->m = m;
    this->p = p;
    this->score = 0;
    // int p = std::pow(2, m);
    for (unsigned int i = 0; i < p; ++i) {
        this->actions.emplace_back(rng_uniform(engine) < 0.5 ? BUY : SELL);
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

// TODO: 三項演算子を使うなどしてもっと簡潔に書く
void MinorityGameStrategy::update_score(const int history_integer, const int excess_demand)
{
    if (excess_demand > 0) {
        if (this->actions.at(history_integer) == BUY) {
            this->score--;
        } else {
            this->score++;
        }
    } else {
        if (this->actions.at(history_integer) == BUY) {
            this->score++;
        } else {
            this->score--;
        }
    }
}