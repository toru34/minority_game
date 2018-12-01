#ifndef MINORITY_GAME_STRATEGY_H_
#define MINORITY_GAME_STRATEGY_H_

#include <vector>

#include "config.h"
#include "base_strategy.h"

class MinorityGameStrategy : public BaseStrategy
{
    int p;
    std::vector<int> actions;
public:
    MinorityGameStrategy(const int);
    float get_score();
    int choose_action(const int);
    void update_score(const int, const int);
};

#endif