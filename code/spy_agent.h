#ifndef SPY_AGENT_H_
#define SPY_AGENT_H_

#include <vector>
#include <iterator>
#include <algorithm>

#include "config.h"

class SpyAgent
{
    std::vector<int> action_history;
    std::vector<int> winning_history;
public:
    SpyAgent() {};
    int choose_action(std::vector<int>&);
    std::vector<int>& get_action_history();
    std::vector<int>& get_winning_history();
    void update_action_history(const int);
    void update_winning_history(const int);
    ~SpyAgent() {};
};

#endif