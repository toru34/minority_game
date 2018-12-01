#ifndef MINORITY_GAME_AGENT_H_
#define MINORITY_GAME_AGENT_H_

#include <memory>
#include <vector>

#include "base_agent.h"
#include "base_strategy.h"
#include "minority_game_strategy.h"

class MinorityGameAgent : public BaseAgent
{
    std::vector<std::shared_ptr<BaseStrategy> > strategies_ptrs;
public:
    MinorityGameAgent(const int, const int);
    int choose_action(const int);
    std::shared_ptr<BaseStrategy> get_best_strategy_ptr();
    std::vector<int>& get_action_history();
    std::vector<int>& get_winning_history();
    void update_action_history(const int);
    void update_winning_history(const int);
    void update_strategy_score(const int, const int);
};

#endif