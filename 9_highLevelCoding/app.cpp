#include <iostream>
#include <fstream>
#include <string>

#define DEVICE_FILE "/dev/my_file"

int main() {


    std::ofstream fileOut(DEVICE_FILE, std::ios::out);
    const std::string dataToWrite = "Hello from C++!";
    fileOut << dataToWrite;
    std::cout << "Written : " << dataToWrite << std::endl;
    fileOut.close();

    std::ifstream fileIn(DEVICE_FILE, std::ios::in);
    std::string content;
    getline(fileIn, content);
    std::cout << "Read : " << content << std::endl;
    fileIn.close();
    return 0;
}
