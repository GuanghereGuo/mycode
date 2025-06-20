#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> out;

int check(const std::string& str) {
    int result = str[1];
    for (int i = 2; str[i] != '*'; ++i) {
        result ^= str[i];
    }
    return result;
}

int convert(const std::string& str) { return std::stoi(str, nullptr, 16); }

void convert_being_time(const std::string& utc_time) {
    int hour = std::stoi(utc_time.substr(0, 2));
    int b_hour = (hour + 8) % 24;
    if (b_hour / 10 == 0) {
        out.push_back("0" + std::to_string(b_hour) + ":" +
                      utc_time.substr(2, 2) + ":" + utc_time.substr(4, 2));
    } else {
        out.push_back(std::to_string(b_hour) + ":" + utc_time.substr(2, 2) +
                      ":" + utc_time.substr(4, 2));
    }
}

int main() {
    std::string str;
    while (std::cin >> str) {
        if (str == "END") break;
        if (str.compare(0, 6, "$GPRMC") == 0) {
            size_t asterisk_pos = str.find('*');
            if (asterisk_pos != std::string::npos) {
                int checksum = check(str);
                int sen_checksum = convert(str.substr(asterisk_pos + 1, 2));
                if (checksum != sen_checksum) {
                    out.emplace_back("error");
                } else {
                    std::string utc_time = str.substr(7, 6);
                    convert_being_time(utc_time);
                }
            }
        }
    }
    for (const auto& entry : out) {
        std::cout << entry << std::endl;
    }
    return 0;
}