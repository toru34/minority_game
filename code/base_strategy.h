#ifndef BASE_STRATEGY_H_
#define BASE_STRATEGY_H_

class BaseStrategy
{
protected:
    float score;
public:
    virtual float get_score() = 0;
    virtual int choose_action(const int) = 0;
    virtual void update_score(const int, const int) = 0;
    virtual ~BaseStrategy() {};
};

#endif