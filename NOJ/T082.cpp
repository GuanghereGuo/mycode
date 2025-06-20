//
// Created by 24087 on 24-9-26.
//
#include <iostream>
#include <vector>
#include <algorithm>

long long max_sum(const std::vector<long long>& nums) {
    if (nums.empty()) return 0;

    const long long max_num = *max_element(nums.begin(), nums.end());

    std::vector<long long> freq(max_num + 1, 0);
    for (const auto num : nums) {
        freq[num]++;
    }

    std::vector<long long> dp(max_num + 1, 0);

    dp[1] = freq[1];

    for (int i = 2; i <= max_num; i++) {
        dp[i] = std::max(dp[i-1], dp[i-2] + i * freq[i]);
    }
    //not delete i or delete i
    return dp[max_num];
}

int main() {
    int n;
    std::cin >> n;
    std::vector<long long> nums(n);

    for (int i = 0; i < n; i++) {
        std::cin >> nums[i];
    }

    std::cout << max_sum(nums);
}
