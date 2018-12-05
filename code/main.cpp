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
#include "utils.h"

// TODO: constをつけられるところはつける

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

void parse_config(std::map<std::string, float>& config, int argc, char** argv)
{
    if (argc == 1) {
        std::cout << "No argument is provided." << std::endl;
    } else {
        for (int i = 1; i < argc; ++i) {
            if (i + 1 < argc) {
                auto _key = std::string(argv[i]);
                auto key = _key.substr(2, _key.size() - 2);
                auto value = std::stof(argv[++i]);
                if (config.count(key)) {
                    config.find(key)->second = value;
                } else {
                    std::cout << "Invalid argument" << std::endl;
                }
            } else {
                std::cout << "Invalid argument" << std::endl;
            }
        }
    }
}

bool is_config_valid(std::map<std::string, float>& config)
{
    for (auto iter = std::begin(config); iter != std::end(config); ++iter) {
        if (iter->second == -1) {
            std::cout << "Parameter \"" << iter->first << "\" is missing." << std::endl;
            return false;
        }
    }

    return true;
}

void create_result_dir_chars(std::map<std::string, float>& config, char* result_dir)
{
    sprintf(result_dir, "../simulation_results/s%d_p%d_eps%.2f_nmins%d_npros%d_nspes%d_niters%d_nruns%d",
        static_cast<int>(config.find("s")->second),
        static_cast<int>(config.find("p")->second),
        config.find("e")->second,
        static_cast<int>(config.find("nm")->second),
        static_cast<int>(config.find("np")->second),
        static_cast<int>(config.find("ns")->second),
        static_cast<int>(config.find("ni")->second),
        static_cast<int>(config.find("nr")->second)
    );
}

void game(std::vector<std::shared_ptr<BaseAgent> >& agents_ptrs, Environment& environment, const float success_rate)
{
    // Get random history integer (x ~ {0, 1, ..., P - 1})
    int history_integer = environment.get_random_history_integer();

    // Get agents' actions
    // TODO: std::accumulateを使う
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
    environment.update_history(actions);
}

void run(std::map<std::string, float>& config, char* result_dir, int r)
{
    Environment environment(config.find("p")->second);

    std::vector<std::shared_ptr<BaseAgent> > agents_ptrs;

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
            config.find("e")->second
        ));
    }

    // Iterate games
    for (int i = 0; i < config.find("ni")->second; ++i) {
        game(
            agents_ptrs,
            environment,
            config.find("r")->second
        );
    }

    auto attendance_history = environment.get_attendance_history();
    save_vector(attendance_history, result_dir, "attendance_history", r); // TODO rとconfig.find("r")->secondが紛らわしいので修正

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

    // TODO: Multiple keysに対応させる
    std::map<std::string, float> config = {
        {"s", -1}, // Number of strategies
        {"p", -1}, // Number of possible histories
        {"e", -1}, // Constant learing rate for passive strategy
        {"nm", -1}, // Number of minority agents
        {"np", -1}, // Number of producer agents
        {"ns", -1}, // Number of speculator agents
        {"ni", -1}, // Number of iterations
        {"nr", -1} // Number of runs
    };

    parse_config(config, argc, argv);
    if (!is_config_valid(config)) {
        std::cout << "Configuration is invalid." << std::endl;
        return 0;
    } else {
        print(config);
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