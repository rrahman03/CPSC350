#include <iostream>
#include <cmath>

int main() {

    // define dTwelfthRootOfTwo
    double dTwelfthRootOfTwo = 1.059463094359;

    // define the reference frequency
    double fR = 16.35;

    // define the speed of sound 
    double speedOfSound = 345.0; 

    // define note names
    std::string notes[] = {"C#", "D", "D#", "C", "D#", "C"};

    // display the reference frequency
    std::cout << "Reference frequency: " << fR << " Hz" << std::endl;

    // display the speed of sound
    std::cout << "Speed of sound: " << speedOfSound << " m/s" << std::endl;

    /// define the wavelength in centimeters per second
    double wavelength_cm = speedOfSound * 100; 

    // define integer to store powers of 2
    long iTwoRaisedToPowerNu;

    // display the header for note frequencies
    std::cout << "\nNote\tNu\tK\tFrequency (Hz)" << std::endl;

    // compute and display frequencies for each note
    for (int nu = 0; nu <= 8; ++nu) {
        iTwoRaisedToPowerNu = pow(2, nu);

        for (int k = 0; k < 12; ++k) {
            // compute the frequencies of the following notes: C#0, D0, D3, C4, D#7, and C8 
            if ((notes[k] == "C#" && nu == 0) || 
                (notes[k] == "D" && nu == 0) ||
                (notes[k] == "D#" && nu == 3) || 
                (notes[k] == "C" && nu == 4) ||
                (notes[k] == "D#" && nu == 7) ||   
                (notes[k] == "C" && nu == 8)) {

                // provided formula
                double frequency = fR * pow(2, nu) * pow(dTwelfthRootOfTwo, k);
                double wavelength = speedOfSound / frequency * 100; 

                // display note name, octave, frequency, and wavelength
                std::cout << "Note: " << notes[k] << ", Nu: " << nu << ", k: " << k << ", Frequency: " << frequency << " Hz, Wavelength: " << wavelength << " cm" << std::endl;
            }
        }
    }

    return 0;
}


