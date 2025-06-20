#include <iostream>

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    int numerator1, denominator1, numerator2, denominator2;
    std::cin >> numerator1;
    getchar();
    std::cin >> denominator1 >> numerator2;
    getchar();
    std::cin >> denominator2;

    int sumNumerator, sumDenominator, diffNumerator, diffDenominator;
    int prodNumerator, prodDenominator, quotNumerator, quotDenominator;
    int sumGcd, diffGcd, prodGcd, quotGcd;

    // Addition
    sumNumerator = numerator1 * denominator2 + denominator1 * numerator2;
    sumDenominator = denominator1 * denominator2;
    sumGcd = gcd(sumNumerator, sumDenominator);
    sumNumerator /= sumGcd;
    sumDenominator /= sumGcd;

    // Subtraction
    diffNumerator = numerator1 * denominator2 - denominator1 * numerator2;
    diffDenominator = denominator1 * denominator2;
    diffGcd = gcd(diffNumerator, diffDenominator);
    diffNumerator /= diffGcd;
    diffDenominator /= diffGcd;

    // Multiplication
    prodNumerator = numerator1 * numerator2;
    prodDenominator = denominator1 * denominator2;
    prodGcd = gcd(prodNumerator, prodDenominator);
    prodNumerator /= prodGcd;
    prodDenominator /= prodGcd;

    // Division
    quotNumerator = numerator1 * denominator2;
    quotDenominator = denominator1 * numerator2;
    quotGcd = gcd(quotNumerator, quotDenominator);
    quotNumerator /= quotGcd;
    quotDenominator /= quotGcd;

    std::cout << "(" << numerator1 << "/" << denominator1 << ")+(" << numerator2 << "/" << denominator2 << ")=" << sumNumerator << "/" << sumDenominator << std::endl;
    std::cout << "(" << numerator1 << "/" << denominator1 << ")-(" << numerator2 << "/" << denominator2 << ")=" << diffNumerator << "/" << diffDenominator << std::endl;
    std::cout << "(" << numerator1 << "/" << denominator1 << ")*(" << numerator2 << "/" << denominator2 << ")=" << prodNumerator << "/" << prodDenominator << std::endl;
    std::cout << "(" << numerator1 << "/" << denominator1 << ")/(" << numerator2 << "/" << denominator2 << ")=" << quotNumerator << "/" << quotDenominator << std::endl;

    return 0;
}
