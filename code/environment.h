#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include <vector>
#include <string>
#include <iostream>

#include "config.h"

class Environment
{
    int p;
    std::vector<int> minority_side_history;
    std::vector<int> buys_history;
    std::vector<int> buys_normal_agents_history;
    std::vector<int> sells_history;
    std::vector<int> attendance_history;
    std::vector<int> excess_demand_history;
    std::vector<int> market_information_history;
public:
    Environment(const int);
    int get_random_history_integer();
    std::vector<int>& get_minority_side_history();
    std::vector<int>& get_attendance_history();
    std::vector<int>& get_buys_history();
    std::vector<int>& get_buys_normal_agents_history();
    std::vector<int>& get_sells_history();
    std::vector<int>& get_excess_demand_history();
    std::vector<int>& get_market_information_history();
    void update_history(const std::vector<int>&, const std::vector<int>&);
};

#endif