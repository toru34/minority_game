#include "environment.h"

Environment::Environment(const int p)
{
    this->p = p;
}

int Environment::get_random_history_integer()
{
    std::uniform_int_distribution<int> rng_history_integer(0, this->p - 1);
    int market_information = rng_history_integer(ENGINE); // x ~ {0, 1, 2, ..., 1-P}
    this->market_information_history.emplace_back(market_information);
    return market_information;
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

std::vector<int>& Environment::get_buys_normal_agents_history()
{
    return this->buys_normal_agents_history;
}

std::vector<int>& Environment::get_sells_history()
{
    return this->sells_history;
}

std::vector<int>& Environment::get_excess_demand_history()
{
    return this->excess_demand_history;
}

std::vector<int>& Environment::get_market_information_history()
{
    return this->market_information_history;
}

void Environment::update_history(const std::vector<int>& actions, const std::vector<int>& actions_normal_agents)
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

    int buys_normal_agents = std::count(std::begin(actions_normal_agents), std::end(actions_normal_agents), BUY);

    this->buys_normal_agents_history.emplace_back(buys_normal_agents);
}