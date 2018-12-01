#ifndef SPECULATOR_AGENT_H_
#define SPECULATOR_AGENT_H_

#include <vector>
#include <memory>

#include "config.h"
#include "base_agent.h"
#include "base_strategy.h"
#include "passive_strategy.h"
#include "active_strategy.h"

class SpeculatorAgent : public BaseAgent
{
    std::vector<std::shared_ptr<BaseStrategy> > strategies_ptrs;
public:
    SpeculatorAgent(const int, const int, const float);
    int choose_action(const int);
    std::shared_ptr<BaseStrategy> get_best_strategy_ptr();
    std::vector<int>& get_action_history();
    std::vector<int>& get_winning_history();
    void update_action_history(const int);
    void update_winning_history(const int);
    void update_strategy_score(const int, const int);
};

#endif