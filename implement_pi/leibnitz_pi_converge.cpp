#include <iostream>
#include <cmath>
#include <iomanip>
// Step One
// encapsulate the for loop to calculate pi from Part 1 in another, outer, for loop
// whos index is n, where n is the upper bound passed to the inner for loop
// n should start at 2 and double in value on each iteration until it reaches 220, or 1048576
int main() {
    for (long long n = 2; n <= (1 << 20); n *= 2) {
        double pi = 0.0;
        for (long long k = 0; k < n; ++k) {
            pi += pow(-1, k) / (2 * k + 1);
        }
        pi *= 4;

        std::cout << std::fixed << std::setprecision(15);
        std::cout << "PI: " << pi << ", n: " << n << std::endl;
    }

    return 0;
}
