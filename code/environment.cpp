#include "environment.h"

Environment::Environment()
{
}

int Environment::get_random_history_integer()
{
    return rng_history_integer(engine); // x ~ {0, 1, 2, ..., 1-P}
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

void Environment::update_history(const std::map<std::string, int> res)
{
    this->minority_side_history.emplace_back(res.find("minority_side")->second);
    this->buys_history.emplace_back(res.find("buys")->second);
    this->sells_history.emplace_back(res.find("sells")->second);
    this->attendance_history.emplace_back(res.find("attendance")->second);
    this->excess_demand_history.emplace_back(res.find("excess_demand")->second);
}