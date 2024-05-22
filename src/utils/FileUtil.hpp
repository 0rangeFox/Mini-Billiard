#ifndef MINI_BILLIARD_FILEUTIL_HPP
#define MINI_BILLIARD_FILEUTIL_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <algorithm>
#include <sstream>
#include "../classes/FileType.h"

static std::vector<std::string> ReadFile(const std::string& path) {
    std::vector<std::string> lines;
    std::ifstream file(path);

    if (file.is_open()) {
        std::string line;

        while (std::getline(file, line))
            lines.push_back(line);

        file.close();
    } else
        std::cerr << "Error: Unable to open file " << path << std::endl;

    return lines;
}

static bool ReadFileStream(const std::string& path, const std::function<bool(std::istringstream)>& lineCallback) {
    for (const std::string& line : ReadFile(path))
        if (!lineCallback(std::istringstream(line)))
            return false;
    return true;
}

static bool ReadFile(const std::string& path, const std::function<bool(const std::string&)>& lineCallback) {
    auto lines = ReadFile(path);
    return std::all_of(lines.begin(), lines.end(), lineCallback);
}

static FileType GetFileType(const std::string& path) {
    const std::string& extension = path.substr(path.find_last_of('.') + 1);

    if (extension == "jpg" || extension == "jpeg" || extension == "png")
        return FileType::IMAGE;
    else if (extension == "obj")
        return FileType::OBJECT;
    else if (extension == "mtl")
        return FileType::MATERIAL;
    else if (extension == "vert")
        return FileType::VERTEX_SHADER;
    else if (extension == "frag")
        return FileType::FRAGMENT_SHADER;
    else
        return FileType::UNKNOWN;
}

#endif //MINI_BILLIARD_FILEUTIL_HPP
