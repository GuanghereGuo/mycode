//
// Created by 24087 on 24-10-8.
//
//
// Created by 24087 on 24-10-8.
//
#include <iostream>
#include <cmath>

int calculate_speed(double temperature, double pressure, int elevation, int runway, int weight, int flaps, int wet) {
    // 检查输入是否在有效范围内
    if (flaps != 1 && flaps != 5 && flaps != 15) {
        return -1;
    }

    if (weight < 41413 || weight > 65000 || runway <= 6900) {
        return -1;
    }

    // 计算温度档和气压档
    int temp_range = std::floor(temperature / 10);
    int pressure_range = std::ceil(pressure);

    // 检查操纵参考表是否存在
    if (temp_range < 0 || temp_range > 7 || pressure_range < 0 || pressure_range > 9) {
        return -1;
    }

    // 根据温度档和气压档查找操纵参考值
    char reference_table[8][10] = {
        {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J', 'K'},
        {'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'U', 'V'},
        {'W', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F'},
        {'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R'},
        {'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B'},
        {'C', 'D', 'E', 'F', 'G', 'H', 'J', 'K', 'L', 'M'},
        {'N', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X'},
        {'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'}
    };

    char reference = reference_table[temp_range][pressure_range];

    // 检查操纵参考表是否存在V1、Vr和V2
    if (reference != 'A' && reference != 'B' && reference != 'C' && reference != 'D' && reference != 'E') {
        return -1;
    }

    // 根据襟翼位置、起飞重量和操纵参考值查找V1、Vr和V2
    int speed_table[3][5] = {
        {117, 126, 134, 142, 151},
        {122, 131, 139, 147, 156},
        {127, 136, 145, 153, 162}
    };

    int speed_index = (flaps - 1) / 7;
    int* speed_row = speed_table[speed_index];

    int v1 = speed_row[weight / 13000];
    int vr = speed_row[weight / 13000] + 11;
    int v2 = speed_row[weight / 13000] + 18;

    // 如果是湿跑道，根据跑道长度和襟翼位置查找折扣值
    if (wet == 1) {
        int discount_table[3][3] = {
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0}
        };

        int discount_index = (flaps - 1) / 7;
        int* discount_row = discount_table[discount_index];

        int discount = discount_row[runway / 1000];

        v1 -= discount;
    }

    std::cout << "V1=" << v1 << "kts Vr=" << vr << "kts V2=" << v2 << "kts\n";

    return 0;
}

int main() {
    double temperature, pressure;
    int elevation, runway, weight, flaps, wet;

    std::cin >> temperature >> pressure;
    std::cin >> elevation >> runway >> weight >> flaps >> wet;

    int result = calculate_speed(temperature, pressure, elevation, runway, weight, flaps, wet);

    if (result == -1) {
        std::cout << "Flight not possible!\n";
    }

}