#include "spy_agent.h"

SpyAgent::SpyAgent()
{
}

int SpyAgent::choose_action(std::vector<int>& actions)
{
    int buys = std::count(std::begin(actions), std::end(actions), BUY);
    int sells = std::count(std::begin(actions), std::end(actions), SELL);
    
    if (buys < sells) {
        return BUY;
    } else if (sells < buys) {
        return SELL;
    } else { // if buys == sells
        return RNG_UNIFORM(ENGINE) < 0.5 ? BUY : SELL;
    }
}