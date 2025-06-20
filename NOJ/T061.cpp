#include <iostream>

void puts_dna1() {
    std::cout << R"(   AT
  T--A
 A----T
T------A
T------A
 G----C
  T--A
   GC
)";
}

void puts_dna2() {
    std::cout << R"(   CG
  C--G
 A----T
A------T
T------A
 A----T
  A--T
   GC
)";
}

void puts_dna3() {
    std::cout << R"(   AT
  C--G
 T----A
C------G
C------G
 T----A
  G--C
   AT
)";
}

int main() {
    int n;
    std::cin >> n;
    for (int i = 1; i <= n / 2; ++i) {
        if (i % 3 == 1)
            puts_dna1();
        else if (i % 3 == 2)
            puts_dna2();
        else
            puts_dna3();
    }
}