#include "producer_agent.h"

// ProducerAgent::ProducerAgent(const int m)
ProducerAgent::ProducerAgent(const int p)
{
    // this->strategy_ptr = std::make_unique<ActiveStrategy>(m);
    this->strategy_ptr = std::make_unique<ActiveStrategy>(p);
}

int ProducerAgent::choose_action(const int history_integer)
{
    int action = this->strategy_ptr->choose_action(history_integer);
    this->action_history.emplace_back(action);

    return action;
}

std::vector<int>& ProducerAgent::get_action_history()
{
    return this->action_history;
}

std::vector<int>& ProducerAgent::get_winning_history()
{
    return this->winning_history;
}

void ProducerAgent::update_action_history(const int action)
{
    this->action_history.emplace_back(action);
}

void ProducerAgent::update_winning_history(const int excess_demand)
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

void ProducerAgent::update_strategy_score(const int history_integer, const int excess_demand)
{
}