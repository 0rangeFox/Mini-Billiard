//
// Created by João Fernandes on 18/05/2024.
//

#ifndef MINI_BILLIARD_FILE_H
#define MINI_BILLIARD_FILE_H

#include <iostream>
#include "../utils/FileUtil.hpp"

#define DIRECTORY_DELIMITER "/\\"
#define EXTENSION_DELIMITER '.'

typedef struct File {
public:
    File() {}

    explicit File(const std::string& path) : type(GetFileType(path)) {
        size_t extPos = path.find_last_of(EXTENSION_DELIMITER),
                namePos = path.find_last_of(DIRECTORY_DELIMITER) + 1;

        this->extension = path.substr(extPos + 1);
        this->fileName = path.substr(namePos, extPos - namePos);
        this->path = path.substr(0, namePos - 1);
    }

    std::string getPath() const { return this->path + '/'; }
    const std::string& getExtension() const { return this->extension; }
    const std::string& getName() const { return this->fileName; }
    std::string getNameWithExtension() const { return this->fileName + '.' + this->getExtension(); }
    std::string getFullPath() const { return this->getPath() + this->getNameWithExtension(); }

    File copyPathToFile(const std::string& file) const { return File{ this->getPath() + file }; }

private:
    FileType type;
    std::string path;
    std::string fileName;
    std::string extension;
} * FilePtr;

#endif //MINI_BILLIARD_FILE_H