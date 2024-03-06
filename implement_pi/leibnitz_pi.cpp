#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <cfloat>

// Step One
// write a program that implements the Leibnitz formula
// using a for loop to calculate for π
// represent π as a variable named pi
// I had chat GBT help me debug/figure out how to implement the equation in c++
int main() {
    long long n;
    std::cout << "Enter the number of terms to approximate pi: ";
    std::cin >> n; // Make sure to input the value of n before using it

    double pi = 0.0;
    for (long long k = 0; k < n; ++k) {
        pi += pow(-1, k) / (2 * k + 1);
    }
    pi *= 4; // Adjust the formula to calculate pi instead of pi/4

    // Step Two 
    // print and display the value of pi to 15 decimal places
    std::cout << std::fixed << std::setprecision(15);

    // Step Three
    // display pi and n on the same line
    // set the width for n to 7
    // print the actual value for pi on the following line
    std::cout << "PI (approx): " << pi << " n: " << std::setw(7) << n << std::endl;
    std::cout << "PI (actual): " << "3.141592653589793" << std::endl;

    std::cout << "Decimal digits of precision: " << DBL_DIG << std::endl;
    std::cout << "Number of base 2 mantissa digits of double precision floating point value: " << DBL_MANT_DIG << std::endl;

    // Step 4
    // use std::nextafter method to determine if the value for pi to 15 digits could have been represented exactly
    double actualPi = 3.141592653589793;
    double nextPi = std::nextafter(actualPi, std::numeric_limits<double>::max());
    std::cout << "Next representable number from 3.141592653589793: " << nextPi << std::endl;

    return 0;
}
