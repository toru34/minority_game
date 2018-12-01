#ifndef ACTIVE_STRATEGY_H_
#define ACTIVE_STRATEGY_H_

#include <cmath>
#include <vector>

#include "config.h"
#include "base_strategy.h"

class ActiveStrategy : public BaseStrategy
{
    int p;
    std::vector<int> actions;
public:
    ActiveStrategy(const int);
    float get_score();
    int choose_action(const int);
    void update_score(const int, const int);
};

#endif