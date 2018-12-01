#include <map>
#include <ctime>
#include <string>
#include <numeric>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sys/stat.h>

#include "minority_game_agent.h"
#include "base_agent.h"
#include "config.h"
#include "environment.h"
#include "producer_agent.h"
#include "speculator_agent.h"

template<typename T>
void save_vector(const std::vector<T>& x, const char* result_dir, const char* file_prefix, const int r)
{
    char path[500];
    sprintf(path, "%s/%s_%d.csv", result_dir, file_prefix, r);
    std::ofstream f;
    f.open(path);
    if (!f.is_open()) {
        std::cout << "Error opening file" << std::endl;
    }
    for (auto &v : x) {
        f << v << ",";
    }
    f << "\n";
    f.close();
}

void game(std::vector<std::shared_ptr<BaseAgent> >& agents_ptrs, Environment& environment, const int p)
{
    // Get random history integer (x ~ {0, 1, ..., P - 1})
    int history_integer = environment.get_random_history_integer();

    // Get agents' actions
    std::vector<int> actions;
    for (auto& agent_ptr : agents_ptrs) {
        int action = agent_ptr->choose_action(history_integer);
        actions.emplace_back(action);
    }

    int buys = std::count(std::begin(actions), std::end(actions), BUY);
    int sells = std::count(std::begin(actions), std::end(actions), SELL);
    int attendance = buys + sells;
    int excess_demand = buys - sells;
    int minority_side = buys > sells ? SELL : BUY;

    for (auto& agent_ptr : agents_ptrs) {
        agent_ptr->update_strategy_score(history_integer, excess_demand);
    }

    // Update winning histories
    for (auto& agent_ptr : agents_ptrs) {
        agent_ptr->update_winning_history(excess_demand);
    }

    // Update history
    std::map<std::string, int> res;
    res.insert(std::pair<std::string, int>("minority_side", minority_side));
    res.insert(std::pair<std::string, int>("buys", buys));
    res.insert(std::pair<std::string, int>("sells", sells));
    res.insert(std::pair<std::string, int>("attendance", attendance));
    res.insert(std::pair<std::string, int>("excess_demand", excess_demand));

    environment.update_history(res);
}

void run(const int s, const int p, const float eps, const int n_minority_agents, const int n_producer_agents, const int n_speculator_agents, const int n_iters, const int n_runs, const int r, const char *result_dir)
{
    Environment environment;

    std::vector<std::shared_ptr<BaseAgent> > agents_ptrs;

    // Minority agents
    for (int i = 0; i < n_minority_agents; ++i) {
        agents_ptrs.emplace_back(std::make_shared<MinorityGameAgent>(s, p));
    }

    // Producer agents
    for (int i = 0; i < n_producer_agents; ++i) {
        agents_ptrs.emplace_back(std::make_shared<ProducerAgent>(p));
    }

    // Speculator agents
    for (int i = 0; i < n_speculator_agents; ++i) {
        agents_ptrs.emplace_back(std::make_shared<SpeculatorAgent>(s, p, eps));
    }

    // Iterate games
    for (int i = 0; i < n_iters; ++i) {
        game(agents_ptrs, environment, p);
    }

    auto attendance_history = environment.get_attendance_history();
    save_vector(attendance_history, result_dir, "attendance_history", r);

    auto buys_history = environment.get_buys_history();
    save_vector(buys_history, result_dir, "buys_history", r);

    auto sells_history = environment.get_sells_history();
    save_vector(sells_history, result_dir, "sells_history", r);

    auto excess_demand_history = environment.get_excess_demand_history();
    save_vector(excess_demand_history, result_dir, "excess_demand_history", r);
}

int main(int argc, char **argv)
{
    std::clock_t start, end;
    start = std::clock();

    // Create dir
    char result_dir[500];
    sprintf(result_dir, "../results/s%d_p%d_eps%.2f_nmins%d_npros%d_nspes%d_niters%d_nruns%d", S, P, EPS, N_MINORITY_AGENTS, N_PRODUCER_AGENTS, N_SPECULATOR_AGENTS, N_ITERS, N_RUNS);

    char command[1000];
    sprintf(command, "rm -rf %s; mkdir -p %s", result_dir, result_dir);
    system(command);

    // Run experiment
    for (int r = 0; r < N_RUNS; ++r)
    {
        run(S, P, EPS, N_MINORITY_AGENTS, N_PRODUCER_AGENTS, N_SPECULATOR_AGENTS, N_ITERS, N_RUNS, r, result_dir);
    }

    end = std::clock();
    std::cout << "S: " << S << ", P: " << P << ", Time: " << (end - start) / 1000000 << "[s]" << std::endl;

    return 0;
}