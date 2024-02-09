#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

std::string parse_line(const std::string& line, const std::string& sourceSID, const std::string& destinationSID) {
    // std::cout << line << "\n:" << sourceSID << ":" << sourceSID.length() << ":" << std::endl;
    if (line.find(sourceSID) == std::string::npos) {
        return line;
    }

    std::string right = line;
    std::string the_new = "";
    while (right.length() > 1) {
        size_t op = right.find('(');
        size_t cp = right.find(')');

        if (op == std::string::npos || cp == std::string::npos) {
            std::cout << line << std::endl << the_new << std::endl;
            return line + the_new;
        }

        std::string current = right.substr(op, cp - op + 1);
        
        size_t pos = current.find(sourceSID);
        if (pos != std::string::npos) {
            the_new = current;
            the_new.replace(pos, sourceSID.length(), destinationSID);
        }

        try {
        right = right.substr(cp + 1);
        } catch(std::exception e) {
            right = "";
        }
    }

    std::cout << line << std::endl << the_new << std::endl;
    return line + the_new;
}

int main() {
    std::string inputFilename;

    std::cout << "Input file path:";
    std::getline(std::cin, inputFilename);

    std::string outPutFilename;
    std::cout << "Output file path:";
    std::getline(std::cin, outPutFilename);

    std::ifstream inputFile(inputFilename);

    std::cout << "Source object SID: ";
    std::string sourceSID;
    std::getline(std::cin, sourceSID);

    std::cout << "Destination object SID: ";
    std::string destinationSID;
    std::getline(std::cin, destinationSID);

    std::ofstream outputFile(outPutFilename);

    while (!inputFile.eof()) {
        std::string line;
        std::getline(inputFile, line);
        std::string result = parse_line(line, sourceSID, destinationSID);
        outputFile << result << std::endl;
    }
    system("pause");
    return 0;
}
