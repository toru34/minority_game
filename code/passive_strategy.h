#ifndef PASSIVE_STRATEGY_H_
#define PASSIVE_STRATEGY_H_

#include "config.h"
#include "base_strategy.h"

class PassiveStrategy : public BaseStrategy
{
    float eps;
public:
    PassiveStrategy(const float);
    float get_score();
    int choose_action(const int);
    void update_score(const int, const int);
};

#endif
