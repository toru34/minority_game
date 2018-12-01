#ifndef PRODUCER_AGENT_H_
#define PRODUCER_AGENT_H_

#include <memory>
#include <vector>

#include "base_agent.h"
#include "active_strategy.h"

class ProducerAgent : public BaseAgent
{
    std::unique_ptr<ActiveStrategy> strategy_ptr;
public:
    ProducerAgent(const int);
    int choose_action(const int);
    std::vector<int>& get_action_history();
    std::vector<int>& get_winning_history();
    void update_action_history(const int);
    void update_winning_history(const int);
    void update_strategy_score(const int, const int);
};

#endif