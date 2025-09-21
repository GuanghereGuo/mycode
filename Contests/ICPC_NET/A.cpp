//
// Created by guanghere on 25-9-7.
//
#include <bits/stdc++.h>

struct Team
{
    std::string name;
    int time = 0, cnt = 0, frozen_cnt = 0, frozen_time = 0;
    std::unordered_map<char, bool> mp;
    std::unordered_map<char, int> buffer;

    void submit(char c, int t, std::string opt)
    {
        if (opt == "Rejected" && !mp[c])
        {
            buffer[c] += 20;
            return;
        }
        if (!mp[c])
        {
            mp[c] = true;
            if (t >= 240)
            {
                frozen_cnt++;
                frozen_time += t + buffer[c];
                buffer[c] = 0;
            }
            else
            {
                cnt++;
                time += t + buffer[c];
                buffer[c] = 0;
            }
        }
    }

    Team() = default;
    explicit Team(std::string&& n) : name(std::move(n))
    {
    }
};
struct Submit
{
    std::string s;
    char c;
    int time;
    std::string opt;
    bool operator<(const Submit& x) const
    {
        return time < x.time;
    }
};

int main()
{
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    int t;
    std::cin >> t;
    while (t--)
    {
        std::unordered_map<std::string, Team> mp;
        int n;
        std::cin >> n;
        std::vector<Submit> sub(n);
        for (auto &[s, c, time, opt] : sub)
        {
            std::cin >> s >> c >> time >> opt;
        }
        std::sort(sub.begin(), sub.end());
        for (auto &[s, c, time, opt] : sub)
        {
            mp[s].submit(c, time, opt);
        }
        std::vector<std::string> best_teams(1);
        int max_n = 0, min_time = INT_MAX;
        for (auto &[name, tm] : mp)
        {
            if (tm.cnt > max_n)
            {
                max_n = tm.cnt;
                best_teams[0] = name;
                min_time = tm.time;
            }
            else if (tm.cnt == max_n)
            {
                if (tm.time < min_time)
                {
                    best_teams.resize(1);
                    best_teams[0] = name;
                    min_time = tm.time;
                }
            }
        }
        std::vector<std::string> candidates = best_teams;
        for (auto &[name, tm] : mp)
        {
            if (tm.cnt + tm.frozen_cnt > max_n)
            {
                candidates.push_back(name);
            }
            else if (tm.cnt + tm.frozen_cnt  == max_n)
            {
                if (tm.time + tm.frozen_time <= min_time)
                {
                    candidates.push_back(name);
                }
            }
        }
        std::sort(candidates.begin(), candidates.end());
        candidates.erase(std::unique(candidates.begin(), candidates.end()), candidates.end());
        for (int i = 0; i < candidates.size(); i++)
        {
            std::cout << candidates[i];
            if (i != candidates.size() - 1)
            {
                std::cout << ' ';
            }
        }
        if (t != 0)
            std::cout << '\n';
    }
}
