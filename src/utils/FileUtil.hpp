//
// Created by João Fernandes on 14/05/2024.
//

#ifndef MINI_BILLIARD_FILEUTIL_HPP
#define MINI_BILLIARD_FILEUTIL_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <functional>

std::vector<std::string> ReadFile(const std::string& fileName) {
    std::vector<std::string> lines;
    std::ifstream file(fileName);

    if (file.is_open()) {
        std::string line;

        while (std::getline(file, line))
            lines.push_back(line);

        file.close();
    } else
        std::cerr << "Error: Unable to open file " << fileName << std::endl;

    return lines;
}

bool ReadFile(const std::string& fileName, const std::function<bool(const std::string&)>& lineCallback) {
//    for (const std::string& line : ReadFile(fileName))
//        if (!lineCallback(line))
//            return false;
//    return true;

    // The above code is same as this
    auto lines = ReadFile(fileName);
    return std::all_of(lines.begin(), lines.end(), lineCallback);
}

#endif //MINI_BILLIARD_FILEUTIL_HPP
