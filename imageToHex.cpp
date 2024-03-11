#include <iostream>
#include <fstream>
#include <iomanip>

int main() {
    // Open the JPEG file in binary mode
    std::ifstream jpegFile("b2cafe84-de32-4e67-aa06-67d90e9960e4 - Copy (2).jpg", std::ios::binary);

    // Check if the file was opened successfully
    if (!jpegFile.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    // Open the output hex file in binary mode
    std::ofstream hexFile("output.hex");

    // Check if the file was opened successfully
    if (!hexFile.is_open()) {
        std::cerr << "Error creating hex file" << std::endl;
        jpegFile.close();
        return 1;
    }

    // Read the JPEG file byte by byte and write the hexadecimal representation to the output file
    char byte;
    while (jpegFile.get(byte)) {
        hexFile << std::setw(2) << std::setfill('0') << std::hex << (int)(unsigned char)byte << " ";
    }

    // Close the files
    jpegFile.close();
    hexFile.close();

    std::cout << "Conversion successful" << std::endl;

    return 0;
}