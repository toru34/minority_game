#include "environment.h"

Environment::Environment(const int p)
{
    this->p = p;
}

int Environment::get_random_history_integer()
{
    std::uniform_int_distribution<int> rng_history_integer(0, this->p - 1);
    return rng_history_integer(ENGINE); // x ~ {0, 1, 2, ..., 1-P}
}

std::vector<int>& Environment::get_minority_side_history()
{
    return this->minority_side_history;
}

std::vector<int>& Environment::get_attendance_history()
{
    return this->attendance_history;
}

std::vector<int>& Environment::get_buys_history()
{
    return this->buys_history;
}

std::vector<int>& Environment::get_sells_history()
{
    return this->sells_history;
}

std::vector<int>& Environment::get_excess_demand_history()
{
    return this->excess_demand_history;
}

void Environment::update_history(const std::vector<int>& actions)
{
    int buys = std::count(std::begin(actions), std::end(actions), BUY);
    int sells = std::count(std::begin(actions), std::end(actions), SELL);
    int attendance = buys + sells;
    int excess_demand = buys - sells;
    int minority_side = buys > sells ? SELL : BUY;

    this->minority_side_history.emplace_back(minority_side);
    this->buys_history.emplace_back(buys);
    this->sells_history.emplace_back(sells);
    this->attendance_history.emplace_back(attendance);
    this->excess_demand_history.emplace_back(excess_demand);
}