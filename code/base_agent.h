#ifndef BASE_AGENT_H_
#define BASE_AGENT_H_

#include <vector>

class BaseAgent
{
protected:
    std::vector<int> action_history;
    std::vector<int> winning_history;
public:
    virtual int choose_action(const int) = 0;
    virtual std::vector<int> &get_action_history() = 0;
    virtual std::vector<int> &get_winning_history() = 0;
    virtual void update_action_history(const int) = 0;
    virtual void update_winning_history(const int) = 0;
    virtual void update_strategy_score(const int, const int) = 0;
    virtual ~BaseAgent(){};
};

#endif