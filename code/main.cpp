#include <map>
#include <cmath>
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
#include "utils.h"
#include "spy_agent.h"

// TODO: constをつけられるところはつける

void game(std::vector<std::shared_ptr<BaseAgent> >& agents_ptrs, std::vector<std::shared_ptr<SpyAgent> >& spy_agents_ptrs, Environment& environment, const float rhok)
{
    // Get random history integer (x ~ {0, 1, ..., P - 1})
    int history_integer = environment.get_random_history_integer();

    // Get agents' actions
    // TODO: std::accumulateを使う
    std::vector<int> actions_normal_agents;
    for (auto& agent_ptr : agents_ptrs) {
        int action = agent_ptr->choose_action(history_integer);
        actions_normal_agents.emplace_back(action);
    }

    // Get spies' actionss
    std::vector<int> actions_spy_agents;
    for (auto& spy_agent_ptr : spy_agents_ptrs) {
        std::shuffle(std::begin(actions_normal_agents), std::end(actions_normal_agents), RNG);
        auto actions_sliced = slice_vector(actions_normal_agents, rhok);
        int action = spy_agent_ptr->choose_action(actions_sliced);
        actions_spy_agents.emplace_back(action);
    }

    auto actions = concat_vectors(actions_normal_agents, actions_spy_agents);
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

    for (auto& spy_agent_ptr : spy_agents_ptrs) {
        spy_agent_ptr->update_winning_history(excess_demand);
    }

    // Update history
    environment.update_history(actions, actions_normal_agents);
}

void run(std::map<std::string, float>& config, char* result_dir, int r)
{
    Environment environment(config.find("p")->second);

    std::vector<std::shared_ptr<BaseAgent> > agents_ptrs;
    std::vector<std::shared_ptr<SpyAgent> > spy_agents_ptrs;

    // Minority agents
    for (int i = 0; i < config.find("nm")->second; ++i) {
        agents_ptrs.emplace_back(std::make_shared<MinorityGameAgent>(
            static_cast<int>(config.find("s")->second),
            static_cast<int>(config.find("p")->second)
        ));
    }

    // Producer agents
    for (int i = 0; i < config.find("np")->second; ++i) {
        agents_ptrs.emplace_back(std::make_shared<ProducerAgent>(
            static_cast<int>(config.find("p")->second)
        ));
    }

    // Speculator agents
    for (int i = 0; i < config.find("ns")->second; ++i) {
        agents_ptrs.emplace_back(std::make_shared<SpeculatorAgent>(
            static_cast<int>(config.find("s")->second),
            static_cast<int>(config.find("p")->second),
            config.find("eps")->second
        ));
    }

    // Spy agents
    for (int i = 0; i < config.find("nspy")->second; ++i) {
        spy_agents_ptrs.emplace_back(std::make_shared<SpyAgent>());
    }

    // Iterate games
    for (int i = 0; i < config.find("ni")->second; ++i) {
        game(
            agents_ptrs,
            spy_agents_ptrs,
            environment,
            config.find("rhok")->second
        );
    }

    auto attendance_history = environment.get_attendance_history();
    save_vector(attendance_history, result_dir, "attendance_history", r);

    auto buys_history = environment.get_buys_history();
    save_vector(buys_history, result_dir, "buys_history", r);

    auto buys_normal_agents_history = environment.get_buys_normal_agents_history();
    save_vector(buys_normal_agents_history, result_dir, "buys_normal_agents_history", r);

    auto sells_history = environment.get_sells_history();
    save_vector(sells_history, result_dir, "sells_history", r);

    auto excess_demand_history = environment.get_excess_demand_history();
    save_vector(excess_demand_history, result_dir, "excess_demand_history", r);

    std::vector<std::vector<int> > winning_histories_minority_game_agents;
    for (auto agent_ptr : agents_ptrs) {
        winning_histories_minority_game_agents.emplace_back(agent_ptr->get_winning_history());
    }
    save_2dvector(winning_histories_minority_game_agents, result_dir, "winning_histories_minority_game_agents", r);

    std::vector<std::vector<int> > winning_histories_spy_agents;
    for (auto spy_agent_ptr : spy_agents_ptrs) {
        winning_histories_spy_agents.emplace_back(spy_agent_ptr->get_winning_history());
    }
    save_2dvector(winning_histories_spy_agents, result_dir, "winning_histories_spy_agents", r);
}

int main(int argc, char **argv)
{
    std::clock_t start, end;
    start = std::clock();

    // TODO: Multiple keysに対応させる
    std::map<std::string, float> config = {
        {"s", -1}, // Number of strategies
        {"p", -1}, // Number of possible histories
        {"eps", -1}, // Constant learing rate for passive strategy
        {"rhok", -1}, // Spy rate
        {"nm", -1}, // Number of minority agents
        {"np", -1}, // Number of producer agents
        {"ns", -1}, // Number of speculator agents
        {"rhos", -1}, // Ratio of spy agents
        {"ni", -1}, // Number of iterations
        {"nr", -1} // Number of runs
    };

    parse_config(config, argc, argv);
    compute_n_spy_agents(config);
    if (!is_config_valid(config)) {
        std::cout << "Configuration is invalid." << std::endl;
        return 0;
    } else {
        // print(config);
    }

    // Create dir
    char result_dir[500];
    create_result_dir_chars(config, result_dir);

    char command[1000];
    sprintf(command, "rm -rf %s; mkdir -p %s", result_dir, result_dir);
    system(command);

    // Run experiment
    for (int r = 0; r < config.find("nr")->second; ++r)
    {
        run(config, result_dir, r);
    }

    end = std::clock();
    std::cout << "Time: " << (end - start) / 1000000 << "[s]" << std::endl;

    return 0;
}