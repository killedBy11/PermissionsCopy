#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <locale>


std::string parse_line(std::string line, const std::string& sourceSID, const std::string& destinationSID, bool overwrite) {
    if (line.find(sourceSID) == std::string::npos || (!overwrite && line.find(destinationSID) != std::string::npos)) {
        return line;
    }

    std::string right = line;
    std::string the_new;
    while (right.length() > 1) {
        size_t op = right.find('(');
        size_t cp = right.find(')');

        if (op == std::string::npos || cp == std::string::npos) {
            std::cout << line << std::endl << the_new << std::endl;
            return line + the_new;
        }

        std::string current = right.substr(op, cp - op + 1);

        size_t pos;

        if (overwrite && std::string::npos != current.find(destinationSID)) {
            pos = line.find(current);
            line.replace(pos, current.length(), "");
            goto JMP;
        }
        
        pos = current.find(sourceSID);
        if (pos != std::string::npos) {
            current.replace(pos, sourceSID.length(), destinationSID);
            the_new += current;
        }

        JMP:
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
    bool overwrite = false;

    std::string overwriteInput;

    std::cout << "In case of conflicting permissions(i.e. the destination user already has permissions on a certain folder/file), do you prefer to OVERWRITE existing permissions or do you want to KEEP existing permissions and disregard the copied permissions: [O/K]";
    std::cin >> overwriteInput;

    if (overwriteInput[0] != 'O' && overwriteInput[0] != 'K' && overwriteInput[0] != 'o' && overwriteInput[0] != 'k') {
        return -1;
    }

    if (overwriteInput[0] == 'O' || overwriteInput[0] == 'o') {
        overwrite = true;
    }


    std::cout << "Input file path:";
    std::getline(std::cin >> std::ws, inputFilename);

    std::string outputFilename;
    std::cout << "Output file path:";
    std::getline(std::cin, outputFilename);

    std::ifstream inputFile(inputFilename, std::ios::binary);

    std::cout << "Source object SID: ";
    std::string sourceSID;
    std::getline(std::cin, sourceSID);

    std::cout << "Destination object SID: ";
    std::string destinationSID;
    std::getline(std::cin, destinationSID);

    std::ofstream outputFile(outputFilename);

    while (!inputFile.eof()) {
        std::string line;
        std::getline(inputFile, line);
        
        line.erase(std::remove_if(line.begin(),line.end(), [](char c) {return c == 0 || c == 13 || c == 10;}), line.end()); 

        std::string result = parse_line(line, sourceSID, destinationSID, overwrite);
        for (const char c : result) {
            outputFile << c;
        }
        outputFile << std::endl;
    }
    outputFile.close();
    system("pause");
    return 0;
}
