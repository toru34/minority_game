#include "spy_agent.h"

int SpyAgent::choose_action(std::vector<int>& actions)
{
    int buys = std::count(std::begin(actions), std::end(actions), BUY);
    int sells = std::count(std::begin(actions), std::end(actions), SELL);
    
    int action;
    if (buys < sells) {
        action = BUY;
    } else if (sells < buys) {
        action = SELL;
    } else { // if buys == sells
        action = RNG_UNIFORM(ENGINE) < 0.5 ? BUY : SELL;
    }
    this->update_action_history(action);
    
    return action;
}

std::vector<int>& SpyAgent::get_action_history()
{
    return this->action_history;
}

std::vector<int>& SpyAgent::get_winning_history()
{
    return this->winning_history;
    
}

void SpyAgent::update_action_history(const int action)
{
    this->action_history.emplace_back(action);
}

void SpyAgent::update_winning_history(const int excess_demand)
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