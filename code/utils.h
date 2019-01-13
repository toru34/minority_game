#ifndef UTILS_H_
#define UTILS_H_

#include <map>
#include <string>
#include <iostream>
#include <iterator>

template <typename T>
void save_vector(const std::vector<T>& x, const char* result_dir, const char* file_prefix, const int r)
{
    char path[1000];
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

template <typename T>
void save_2dvector(const std::vector<std::vector<T> >& x, const char* result_dir, const char* file_prefix, const int r)
{
    char path[1000];
    sprintf(path, "%s/%s_%d.csv", result_dir, file_prefix, r);
    std::ofstream f;
    f.open(path);
    if (!f.is_open()) {
        std::cout << "Error opening file" << std::endl;
    }
    for (auto& v : x) {
        for (auto& a : v) {
            f << a << ",";
        }
        f << "\n";
    }
    f.close();
}

void compute_n_spy_agents(std::map<std::string, float>& config)
{
    int nspy = std::floor((config.find("rhos")->second / (1 - config.find("rhos")->second)) * config.find("nm")->second);
    config.insert(std::pair<std::string, float>("nspy", nspy));
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
    sprintf(result_dir, "../data/simulation/s%d_p%d_eps%.2f_rhok%.2f_rhos%.2f_nmins%d_npros%d_nspes%d_niters%d_nruns%d",
        static_cast<int>(config.find("s")->second),
        static_cast<int>(config.find("p")->second),
        config.find("eps")->second,
        config.find("rhok")->second,
        config.find("rhos")->second,
        static_cast<int>(config.find("nm")->second),
        static_cast<int>(config.find("np")->second),
        static_cast<int>(config.find("ns")->second),
        static_cast<int>(config.find("ni")->second),
        static_cast<int>(config.find("nr")->second)
    );
}

template <typename T>
std::vector<T> slice_vector(const std::vector<T>& x, float rate)
{
    auto iter_first = std::begin(x);
    auto iter_last = std::begin(x) + std::floor(x.size() * rate);

    std::vector<T> x_sliced(iter_first, iter_last);
    return x_sliced;
}

template <typename T>
std::vector<T> concat_vectors(std::vector<T>& x1, std::vector<T>& x2)
{
    std::vector<T> x;

    // TODO: stdにbuilt-inの関数があればそれを使う
    for (auto& v : x1) {
        x.emplace_back(v);
    }
    for (auto& v : x2) {
        x.emplace_back(v);
    }

    return x;
}

template <typename T1, typename T2>
void print(std::map<T1, T2>& x)
{
    std::string str = "{";
    for (auto iter = std::begin(x); iter != std::end(x); ++iter) {
        str += "\"" + std::string(iter->first) + "\": " + std::to_string(iter->second) + "\", ";
    }
    str.erase(str.size() - 2, 2);
    str += "}";

    std::cout << str << std::endl;
}

template <typename T>
void print(std::vector<T>& x)
{
    std::string str = "{";
    for (auto iter = std::begin(x); iter != std::end(x); ++iter) {
        str += std::to_string(*iter) + ", ";
    }
    str.erase(str.size() - 2, 2);
    str += "}";

    std::cout << str << std::endl;
}

#endif