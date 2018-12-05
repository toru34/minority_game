#ifndef SPY_AGENT_H_
#define SPY_AGENT_H_

#include <vector>
#include <iterator>
#include <algorithm>

#include "config.h"

class SpyAgent
{
public:
    SpyAgent();
    int choose_action(std::vector<int>&);
};

#endif