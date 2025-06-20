    //
    // Created by guanghere on 25-4-12.
    //
    #include <iostream>
    #include <vector>

    int main() {
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);
        std::cout.tie(nullptr);

        int a1, a2, n;
        std::cin >> a1 >> a2 >> n;
        std::vector<int> vec = {a1, a2};
        int idx = 0;
        while (vec.size() < n) {
            int to_push = vec[idx++] * vec[idx];
            std::vector<int> tmp;
            if (to_push == 0) {
                vec.push_back(0);
            } else {
                while (to_push) {
                    tmp.push_back(to_push % 10);
                    to_push /= 10;
                }
                for (int i = (int)tmp.size() - 1; i >= 0; i--) {
                    vec.push_back(tmp[i]);
                }
            }
        }
        for (int i = 0; i < n; i++) {
            std::cout << vec[i] << " \n"[i == n - 1];
        }
    }