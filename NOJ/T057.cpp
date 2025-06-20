#include <iostream>
#include <string>

std::string ans;

int strToNum(const std::string& str) {
    if (str.find("zero") != std::string::npos) return 0;
    if (str.find("ten") != std::string::npos) return 10;
    if (str.find("eleven") != std::string::npos) return 11;
    if (str.find("twelve") != std::string::npos) return 12;
    if (str.find("thirteen") != std::string::npos) return 13;
    if (str.find("fourteen") != std::string::npos) return 14;
    if (str.find("fifteen") != std::string::npos) return 15;
    if (str.find("sixteen") != std::string::npos) return 16;
    if (str.find("seventeen") != std::string::npos) return 17;
    if (str.find("eighteen") != std::string::npos) return 18;
    if (str.find("nineteen") != std::string::npos) return 19;

    int unit = 0, decade = 0;
    if (str.find("one") != std::string::npos) unit = 1;
    if (str.find("two") != std::string::npos) unit = 2;
    if (str.find("three") != std::string::npos) unit = 3;
    if (str.find("four") != std::string::npos) unit = 4;
    if (str.find("five") != std::string::npos) unit = 5;
    if (str.find("six") != std::string::npos) unit = 6;
    if (str.find("seven") != std::string::npos) unit = 7;
    if (str.find("eight") != std::string::npos) unit = 8;
    if (str.find("nine") != std::string::npos) unit = 9;
    if (str.find("twenty") != std::string::npos) decade = 20;
    if (str.find("thirty") != std::string::npos) decade = 30;
    if (str.find("forty") != std::string::npos) decade = 40;
    if (str.find("fifty") != std::string::npos) decade = 50;
    if (str.find("sixty") != std::string::npos) decade = 60;
    if (str.find("seventy") != std::string::npos) decade = 70;
    if (str.find("eighty") != std::string::npos) decade = 80;
    if (str.find("ninety") != std::string::npos) decade = 90;
    return unit + decade;
}

void numToStr(int n) {
    switch (n) {
        case 0: ans = "zero"; return;
        case 11: ans = "eleven"; return;
        case 12: ans = "twelve"; return;
        case 13: ans = "thirteen"; return;
        case 14: ans = "fourteen"; return;
        case 15: ans = "fifteen"; return;
        case 16: ans = "sixteen"; return;
        case 17: ans = "seventeen"; return;
        case 18: ans = "eighteen"; return;
        case 19: ans = "nineteen"; return;
        default: break;
    }

    int decade = (n / 10) % 10, unit = n % 10;
    switch (decade) {
        case 2: ans = "twenty"; break;
        case 3: ans = "thirty"; break;
        case 4: ans = "forty"; break;
        case 5: ans = "fifty"; break;
        case 6: ans = "sixty"; break;
        case 7: ans = "seventy"; break;
        case 8: ans = "eighty"; break;
        case 9: ans = "ninety"; break;
        default: break;
    }

    if (decade && unit) ans += "-";

    switch (unit) {
        case 1: ans += "one"; break;
        case 2: ans += "two"; break;
        case 3: ans += "three"; break;
        case 4: ans += "four"; break;
        case 5: ans += "five"; break;
        case 6: ans += "six"; break;
        case 7: ans += "seven"; break;
        case 8: ans += "eight"; break;
        case 9: ans += "nine"; break;
        default: break;
    }
}

int main() {
    std::string a, b;
    std::cin >> a >> b;

    numToStr(strToNum(a) + strToNum(b));
    std::cout << ans << std::endl;
    return 0;
}