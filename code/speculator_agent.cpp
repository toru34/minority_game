#include "speculator_agent.h"

SpeculatorAgent::SpeculatorAgent(const int s, const int p, const float eps)
{
    // Passive Strategy
    this->strategies_ptrs.emplace_back(std::make_shared<PassiveStrategy>(eps));

    // Active Strategy
    for (int i = 0; i < s; ++i) {
        this->strategies_ptrs.emplace_back(std::make_shared<ActiveStrategy>(p));
    }
}

int SpeculatorAgent::choose_action(const int history_integer)
{
    std::shared_ptr<BaseStrategy> best_strategy_ptr = this->get_best_strategy_ptr();
    int action = best_strategy_ptr->choose_action(history_integer);
    this->action_history.emplace_back(action);

    return action;
}

std::shared_ptr<BaseStrategy> SpeculatorAgent::get_best_strategy_ptr()
{
    int best_score = - INF;
    std::shared_ptr<BaseStrategy> best_strategy_ptr;
    for (auto& strategy_ptr : this->strategies_ptrs) {
        if (strategy_ptr->get_score() > best_score) {
            best_score = strategy_ptr->get_score();
            best_strategy_ptr = strategy_ptr;
        }
    }
    return best_strategy_ptr;
}

std::vector<int>& SpeculatorAgent::get_action_history()
{
    return this->action_history;
}

std::vector<int>& SpeculatorAgent::get_winning_history()
{
    return this->winning_history;
}

void SpeculatorAgent::update_action_history(const int action)
{
    this->action_history.emplace_back(action);
}

void SpeculatorAgent::update_winning_history(const int excess_demand)
{
    int action = this->action_history.back();
    int result = action * excess_demand;

    if (result < 0) {
        this->winning_history.emplace_back(WIN);
    } else if (result == 0) {
        this->winning_history.emplace_back(EVEN);
    } else {
        this->winning_history.emplace_back(LOSE);
    }
}

void SpeculatorAgent::update_strategy_score(const int history_integer, const int excess_demand)
{
    for (auto& strategy_ptr : this->strategies_ptrs) {
        strategy_ptr->update_score(history_integer, excess_demand);
    }
}