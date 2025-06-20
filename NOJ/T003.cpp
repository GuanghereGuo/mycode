#include <iostream>
#include <limits>
#include <climits>

using namespace std;

void outputTypeInfo(int d) {
        case 1:
            cout << sizeof(char) << ',' << int(numeric_limits<char>::min()) << ',' << int(numeric_limits<char>::max()) << endl;
        break;
        case 2:
            cout << sizeof(unsigned char) << ',' << int(numeric_limits<unsigned char>::min()) << ',' << int(numeric_limits<unsigned char>::max()) << endl;
        break;
        case 3:
            cout << sizeof(short) << ',' << numeric_limits<short>::min() << ',' << numeric_limits<short>::max() << endl;
        break;
        case 4:
            cout << sizeof(unsigned short) << ',' << numeric_limits<unsigned short>::min() << ',' << numeric_limits<unsigned short>::max() << endl;
        break;
        case 5:
            cout << sizeof(int) << ',' << numeric_limits<int>::min() << ',' << numeric_limits<int>::max() << endl;
        break;
        case 6:
            cout << sizeof(unsigned int) << ',' << numeric_limits<unsigned int>::min() << ',' << numeric_limits<unsigned int>::max() << endl;
        break;
        case 7:
            cout << sizeof(long) << ',' << numeric_limits<long>::min() << ',' << numeric_limits<long>::max() << endl;
        break;
        case 8:
            cout << sizeof(unsigned long) << ',' << numeric_limits<unsigned long>::min() << ',' << numeric_limits<unsigned long>::max() << endl;
        break;
        case 9:
            cout << sizeof(long long) << ',' << numeric_limits<long long>::min() << ',' << numeric_limits<long long>::max() << endl;
        break;
        case 10:
            cout << sizeof(unsigned long long) << ',' << numeric_limits<unsigned long long>::min() << ',' << numeric_limits<unsigned long long>::max() << endl;
        break;
        default:
            cout << "Invalid input" << endl;
    }
}

int main() {
    int d;
    cin >> d;
    outputTypeInfo(d);
    return 0;
}
