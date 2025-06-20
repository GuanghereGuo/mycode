#include <iostream>
#include <vector>

int terSearch(const std::vector<int>& arr, int k) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid1 = left + (right - left) / 3;
        int mid2 = right - (right - left) / 3;
        if (k == arr[mid1]) return mid1;
        if (k == arr[mid2]) return mid2;
        if (k < arr[mid1]) right = mid1 - 1;
        else if (k > arr[mid2]) left = mid2 + 1;
        else {
            left = mid1 + 1;
            right = mid2 - 1;
        }
    }
    return -1;
}

int main() {
    int n, k;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) std::cin >> arr[i];
    std::cin >> k;
    int result = terSearch(arr, k);
    std::cout << k << " in [" << result << "]" << std::endl;
}