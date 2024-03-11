#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>

int main() {
    // Open the hex file in text mode
    std::ifstream hexFile("output.hex");

    // Check if the file was opened successfully
    if (!hexFile.is_open()) {
        std::cerr << "Error opening hex file" << std::endl;
        return 1;
    }

    // Open the output image file in binary mode
    std::ofstream imageFile("output_image.jpg", std::ios::binary);

    // Check if the file was opened successfully
    if (!imageFile.is_open()) {
        std::cerr << "Error creating image file" << std::endl;
        hexFile.close();
        return 1;
    }

    // Read hex values from the file and convert them back to binary
    std::string hexValue;
    while (hexFile >> std::setw(2) >> hexValue) {
        std::istringstream hexStream(hexValue);
        int byteValue;
        hexStream >> std::hex >> byteValue;
        std::cout << byteValue << " ";
        char byte = static_cast<char>(byteValue);
        imageFile.put(byte);
    }

    // Close the files
    hexFile.close();
    imageFile.close();

    std::cout << "Conversion back to image successful" << std::endl;

    return 0;
}