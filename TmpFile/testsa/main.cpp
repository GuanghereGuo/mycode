#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <random>
#include <numeric>
#include <limits>
#include <cmath>
#include <thread>
#include <windows.h>
#include <future>
#include <sstream>
#include <stdexcept>

const int n_emp = 280;  // 员工数
const int n_task = 100; // 任务数

// 从TXT文件中读取矩阵
std::vector<std::vector<double>> read_matrix(const std::string& filename, int rows, int cols) {
    std::vector<std::vector<double>> matrix(rows, std::vector<double>(cols));
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("无法打开文件: " + filename);
    }
    std::string line;
    int row = 0;
    while (std::getline(file, line) && row < rows) {
        std::stringstream ss(line);
        int col = 0;
        double value;
        while (ss >> value && col < cols) {
            matrix[row][col] = value;
            col++;
        }
        if (col != cols) {
            throw std::runtime_error("列数不匹配: 第 " + std::to_string(row + 1) + " 行");
        }
        row++;
    }
    if (row != rows) {
        throw std::runtime_error("行数不匹配: " + filename);
    }
    file.close();
    return matrix;
}

// 计算任务的不满意度
double task_diss(int t, const std::unordered_set<int>& es, const std::vector<std::vector<double>>& diss) {
    if (es.empty()) return 0.0;
    double sum = 0.0;
    for (int e : es) {
        sum += diss[e][t];
    }
    return sum / es.size();
}

// 计算任务的负面影响
double task_neg_impact(const std::unordered_set<int>& es, const std::vector<std::vector<double>>& neg) {
    double impact = 0.0;
    for (auto it1 = es.begin(); it1 != es.end(); ++it1) {
        auto it2 = it1;
        ++it2;
        for (; it2 != es.end(); ++it2) {
            int e1 = *it1;
            int e2 = *it2;
            impact += neg[std::min(e1, e2)][std::max(e1, e2)];
        }
    }
    return impact;
}

// 初始化分配
struct InitResult {
    std::vector<std::vector<int>> assign;
    std::unordered_map<int, int> e2t;
    std::vector<std::unordered_set<int>> t2e;
    double obj;
};

InitResult init_assign(const std::vector<std::vector<double>>& diss,
                       const std::vector<std::vector<double>>& neg,
                       std::mt19937& gen) {
    std::vector<int> emps(n_emp);
    std::iota(emps.begin(), emps.end(), 0);
    std::vector<int> sizes(n_task, 2);
    int extra = n_emp - 2 * n_task;
    for (int i = 0; i < extra; ++i) {
        sizes[i]++;
    }

    double best_obj = std::numeric_limits<double>::infinity();
    InitResult best_result;

    for (int iter = 0; iter < 1000; ++iter) {
        std::shuffle(emps.begin(), emps.end(), gen);
        std::vector<std::vector<int>> assign(n_task);
        int start = 0;
        for (int t = 0; t < n_task; ++t) {
            int s = sizes[t];
            assign[t].assign(emps.begin() + start, emps.begin() + start + s);
            start += s;
        }
        std::unordered_map<int, int> e2t;
        std::vector<std::unordered_set<int>> t2e(n_task);
        for (int t = 0; t < n_task; ++t) {
            for (int e : assign[t]) {
                e2t[e] = t;
                t2e[t].insert(e);
            }
        }
        double total_diss = 0.0;
        double total_neg = 0.0;
        for (int t = 0; t < n_task; ++t) {
            total_diss += task_diss(t, t2e[t], diss);
            total_neg += task_neg_impact(t2e[t], neg);
        }
        double obj = total_diss + total_neg;
        if (obj < best_obj) {
            best_obj = obj;
            best_result = {assign, e2t, t2e, obj};
        }
    }
    return best_result;
}

// 移动操作
struct MoveChanges {
    int emp;
    int from;
    int to;
};

MoveChanges move(std::unordered_map<int, int>& e2t,
                 std::vector<std::unordered_set<int>>& t2e,
                 std::mt19937& gen) {
    std::uniform_int_distribution<> emp_dist(0, n_emp - 1);
    std::uniform_int_distribution<> task_dist(0, n_task - 1);
    int e;
    int curr_t;
    do {
        e = emp_dist(gen);
        curr_t = e2t[e];
    } while (t2e[curr_t].size() <= 2);
    int new_t = curr_t;
    while (new_t == curr_t) {
        new_t = task_dist(gen);
    }
    MoveChanges changes = {e, curr_t, new_t};
    t2e[curr_t].erase(e);
    t2e[new_t].insert(e);
    e2t[e] = new_t;
    return changes;
}

// 回退操作
void revert(const MoveChanges& changes,
            std::vector<std::unordered_set<int>>& t2e,
            std::unordered_map<int, int>& e2t) {
    int e = changes.emp;
    int from = changes.from;
    int to = changes.to;
    t2e[to].erase(e);
    t2e[from].insert(e);
    e2t[e] = from;
}

// 计算增量
struct DeltaResult {
    double d;
    double new_f_diss;
    double new_t_diss;
    double new_neg_impact_f;
    double new_neg_impact_t;
};

DeltaResult delta(const std::vector<std::unordered_set<int>>& t2e,
                  const std::vector<double>& t_diss,
                  const std::vector<double>& neg_impact,
                  const std::vector<std::vector<double>>& diss,
                  const std::vector<std::vector<double>>& neg,
                  const MoveChanges& changes) {
    int e = changes.emp;
    int f = changes.from;
    int t = changes.to;
    double new_f_diss = task_diss(f, t2e[f], diss);
    double new_t_diss = task_diss(t, t2e[t], diss);
    double new_neg_impact_f = task_neg_impact(t2e[f], neg);
    double new_neg_impact_t = task_neg_impact(t2e[t], neg);
    double d_diss = (new_f_diss - t_diss[f]) + (new_t_diss - t_diss[t]);
    double d_neg = (new_neg_impact_f - neg_impact[f]) + (new_neg_impact_t - neg_impact[t]);
    double d = d_diss + d_neg;
    return {d, new_f_diss, new_t_diss, new_neg_impact_f, new_neg_impact_t};
}

// 模拟退火算法
std::tuple<std::vector<std::vector<int>>, double, std::vector<double>> sa(
    const std::vector<std::vector<double>>& diss,
    const std::vector<std::vector<double>>& neg,
    std::mt19937& gen) {
    auto [assign, e2t, t2e, obj] = init_assign(diss, neg, gen);
    std::vector<double> t_diss(n_task);
    std::vector<double> neg_impact(n_task);
    double curr_obj = 0.0;
    for (int t = 0; t < n_task; ++t) {
        t_diss[t] = task_diss(t, t2e[t], diss);
        neg_impact[t] = task_neg_impact(t2e[t], neg);
        curr_obj += t_diss[t] + neg_impact[t];
    }
    double best_obj = curr_obj;
    std::vector<std::vector<int>> best_assign = assign;
    std::vector<double> obj_history;

    double T = 1e4;
    double alpha = 0.9995;
    double min_T = 1e-5;
    int iters = n_emp;

    std::uniform_real_distribution<> rand(0.0, 1.0);

    while (T > min_T) {
        for (int i = 0; i < iters; ++i) {
            MoveChanges changes = move(e2t, t2e, gen);
            DeltaResult res = delta(t2e, t_diss, neg_impact, diss, neg, changes);
            double d = res.d;
            if (d < 0 || rand(gen) < std::exp(-d / T)) {
                t_diss[changes.from] = res.new_f_diss;
                t_diss[changes.to] = res.new_t_diss;
                neg_impact[changes.from] = res.new_neg_impact_f;
                neg_impact[changes.to] = res.new_neg_impact_t;
                curr_obj += d;
                if (curr_obj < best_obj) {
                    best_obj = curr_obj;
                    best_assign = std::vector<std::vector<int>>(n_task);
                    for (int t = 0; t < n_task; ++t) {
                        best_assign[t] = std::vector<int>(t2e[t].begin(), t2e[t].end());
                    }
                }
            } else {
                revert(changes, t2e, e2t);
            }
            obj_history.push_back(curr_obj);
        }
        T *= alpha;
    }
    return {best_assign, best_obj, obj_history};
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    auto start_time = std::chrono::high_resolution_clock::now();

    try {
        // 读取数据
        std::vector<std::vector<double>> diss = read_matrix("../diss.txt", n_emp, n_task);
        std::vector<std::vector<double>> neg = read_matrix("../neg.txt", n_emp, n_emp);

        auto end_read_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> read_diff = end_read_time - start_time;
        std::cout << "读取数据运行时间: " << read_diff.count() << " 秒\n";

        // 多线程模拟退火
        std::random_device rd;
        std::mt19937 gen(rd());
        int num_runs = 8;
        std::vector<std::future<std::tuple<std::vector<std::vector<int>>, double, std::vector<double>>>> futures;

        for (int run = 0; run < num_runs; ++run) {
            futures.push_back(std::async(std::launch::async, sa, std::ref(diss), std::ref(neg), std::ref(gen)));
        }

        std::vector<std::tuple<std::vector<std::vector<int>>, double, std::vector<double>>> results;
        for (auto& future : futures) {
            results.push_back(future.get());
        }

        auto best_result = *std::min_element(results.begin(), results.end(),
            [](const auto& a, const auto& b) { return std::get<1>(a) < std::get<1>(b); });
        auto [best_assign, best_obj, obj_history] = best_result;

        auto end_sa_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> sa_diff = end_sa_time - end_read_time;
        std::cout << "模拟退火算法运行时间: " << sa_diff.count() << " 秒\n";

        // 输出结果到控制台
        std::cout << "Best Total Objective: " << best_obj << '\n';


        // 保存分配结果到TXT
        std::ofstream assign_file("assignment_result.txt");
        if (!assign_file.is_open()) {
            throw std::runtime_error("无法创建 assignment_result.txt");
        }
        for (int t = 0; t < n_task; ++t) {
            assign_file << "Task " << t << ": ";
            for (int e : best_assign[t]) {
                assign_file << e << " ";
            }
            assign_file << '\n';
        }
        assign_file.close();

        // 保存目标函数历史到TXT
        std::ofstream obj_file("obj_history.txt");
        if (!obj_file.is_open()) {
            throw std::runtime_error("无法创建 obj_history.txt");
        }
        for (double obj : obj_history) {
            obj_file << obj << '\n';
        }
        obj_file.close();

        std::cout << "结果已保存到 assignment_result.txt 和 obj_history.txt\n";
        // 计算write运行时间
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> total_diff = end_time - end_sa_time;
        std::cout << "写入文件运行时间: " << total_diff.count() << " 秒\n";
    }
    catch (const std::exception& e) {
        std::cerr << "错误: " << e.what() << '\n';
        return 1;
    }
    auto end_time = std::chrono::high_resolution_clock::now();

    return 0;
}