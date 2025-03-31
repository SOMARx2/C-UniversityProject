#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "reader.h"
#include "readerUtils.h"
#include "commandUtils.h"

template<typename key, typename value>
key getKey(std::map<key, value> const &map, value const& valueToFind) {
    key last;

    for (auto [f, s]: map) {
        if (valueToFind == s) {
            return f;
        }
        last = f;
    }

    return last;
}

FReader::FReader(std::string file, std::string password) : file(std::move(file)), password(std::move(password)) {
    nonEncodedInfo = std::map<int, std::string>();
    nonEncodedInfo.insert({10, "hr"});
    nonEncodedInfo.insert({21, "mn"});
    nonEncodedInfo.insert({32, "sc"});
    nonEncodedInfo.insert({0, "size"});
    setCurrentTime();

    std::vector<std::string> content = getFileContent();

    if (content.at(0).size() < 4) {
        content.at(0) = "0000";
        setFileContent(content);
    }
}

void FReader::addLines(std::vector<std::string> const &lines) {
    size_t size = getSize();

    for (auto const &elem: lines) {
        insertValue((int) size, encrypt(elem, password));
        size++;
    }
}

std::vector<int> FReader::findValues(std::string const &value, int const &parameterId) {
    auto fileContent = getFileContent();
    std::vector<int> result;

    removeNonEncoded(fileContent);

    for (int i = parameterId % 5; i < getSize(); i += 5) {
        if (decrypt(fileContent.at(i), password) == value) {
            result.push_back(i);
        }
    }

    return result;
}

std::vector<std::string> FReader::getInfo(int line) {
    int parametersQuantity = 5;

    auto fileContent = getFileContent();
    std::vector<std::string> result;
    line = line - line % parametersQuantity;

    removeNonEncoded(fileContent);

    for (int i = line; i < line + 5; i++) {
        result.push_back(decrypt(fileContent.at(i), password));
    }

    return result;
}

void FReader::removeLines(int const &from, int const &size, bool const& isUpdateCounter) {
    auto fileNewContent = getFileContent();
    auto nonEncodedInfoValues = std::map<int, std::string>();

    nonEncodedInfoValues = removeNonEncoded(fileNewContent);
    fileNewContent.erase(fileNewContent.begin() + from, fileNewContent.begin() + from + size);
    addNonEncoded(nonEncodedInfoValues, fileNewContent);

    setFileContent(fileNewContent);

    if (isUpdateCounter) {
        overrideValueInLine(0, numberToString(
                stringToInt(getFileContent().at(0).size() > 4 ?
                            getFileContent().at(0).substr(0, 4) : getFileContent().at(0)
                ) - size, 4));
    }
}

void FReader::insertValue(int const &line, std::string const &value, bool isEncrypt) {
    auto fileNewContent = getFileContent();
    auto nonEncodedInfoValues = std::map<int, std::string>();

    nonEncodedInfoValues = removeNonEncoded(fileNewContent);
    fileNewContent.insert(fileNewContent.begin() + line, value);
    addNonEncoded(nonEncodedInfoValues, fileNewContent);

    deleteEmptySpaces(fileNewContent);

    setFileContent(fileNewContent);


    overrideValueInLine(0, numberToString(
            stringToInt(getFileContent().at(0).size() > 4 ?
                        getFileContent().at(0).substr(0, 4) : getFileContent().at(0)
            ) + 1, 4));
}

void FReader::setValueInLine(int const &line, std::string const &value, bool isEncode) {
    auto fileNewContent = getFileContent();
    std::string valueToSave = isEncode ? encrypt(value, password) : value;

    if (fileNewContent.size() > line) {
        if (nonEncodedInfo[line].empty()) {
            fileNewContent.at(line) = valueToSave;
        } else {
            if (fileNewContent.at(line).size() >= nonEncodedInfo[line].size()) {
                fileNewContent.at(line) =
                        fileNewContent.at(line).substr(0, nonEncodedInfo[line].size());
            } else {
                fileNewContent.at(line) = "";
            }

            fileNewContent.at(line) += valueToSave;
        }
    } else {
        addElem(fileNewContent, valueToSave, line);
    }

    setFileContent(fileNewContent);
}

void FReader::removeCategory(std::string category) {
    std::vector<std::string> fileContent = getFileContent();
    removeNonEncoded(fileContent);

    for (int i = getSize(); i < getSize() + getCategorySize(); i++) {
        if (category == decrypt(fileContent.at(i), password)) {
            removeLines(i, 1, false);
            return;
        }
    }
}

void FReader::addCategory(std::string category) {
    std::vector<std::string> fileContent = getFileContent();
    removeNonEncoded(fileContent);
    setValueInLine(getSize() + getCategorySize(), encrypt(category, password));
}

std::vector<std::string> FReader::getCategories() {
    std::vector<std::string> result;
    std::vector<std::string> fileContent = getFileContent();

    removeNonEncoded(fileContent);

    for (int i = getSize(); i < getSize() + getCategorySize(); i++) {
        result.push_back(decrypt(fileContent.at(i), password));
    }

    return result;
}

std::vector<std::vector<std::string>> FReader::getAllPasswords() {
    std::vector<std::vector<std::string>> result;

    for (int i = 0; i < getPasswordSize(); i++) {
        result.push_back(getInfo(i * 5));
    }

    return result;
}

int FReader::getPasswordSize() {
    return getSize() / 5;
}

size_t FReader::getSize() {
    auto fileContent = getFileContent();

    if (fileContent.at(0).size() > 4) {
        return stringToInt(fileContent.at(0).substr(0, 4));
    } else {
        return 0;
    }

}

size_t FReader::getCategorySize() {
    int result = 0;
    auto fileContent = getFileContent();
    removeNonEncoded(fileContent);

    for (int i = getSize(); i < fileContent.size() && !fileContent.at(i).empty(); i++) {
        result++;
    }

    return result;
}

void FReader::setFileContent(std::vector<std::string> const &content) {
    std::ofstream writeStream(file, std::ios::out);

    for (auto const &elem: content) {
        writeStream << elem << "\n";
    }
}

std::vector<std::string> FReader::getFileContent() {
    std::fstream readStream(file);
    auto result = std::vector<std::string>();

    for (auto copiedLine = std::string(); std::getline(readStream, copiedLine);) {
        result.push_back(copiedLine);
    }
    readStream.close();
    return result;
}

void FReader::overrideValueInLine(int const &line, std::string const &value) {
    auto fileNewContent = getFileContent();

    if (fileNewContent.size() > line) {
        if (fileNewContent.at(line).size() > value.size()) {
            fileNewContent.at(line) = value
                                      + fileNewContent.at(line)
                                              .substr(value.size(),
                                                      fileNewContent.at(line).size() - value.size());
        } else {
            fileNewContent.at(line) = value;
        }
    } else {
        addElem(fileNewContent, value, line);
    }

    setFileContent(fileNewContent);
}

void FReader::setCurrentTime() {
    time_t currentTimeSec = time(nullptr);
    tm *currentTime = localtime(&currentTimeSec);

    std::string code = "hr";
    overrideValueInLine(
            getKey(nonEncodedInfo, code),
            timeToString(currentTime->tm_hour));
    code = "mn";
    overrideValueInLine(
            getKey(nonEncodedInfo, code),
            timeToString(currentTime->tm_min));
    code = "sc";
    overrideValueInLine(
            getKey(nonEncodedInfo, code),
            timeToString(currentTime->tm_sec));
}

bool isFileValid(std::string const &path) {
    std::ifstream stream(path);
    return stream.good();
}

std::map<int, std::string> FReader::removeNonEncoded(std::vector<std::string> &fileNewContent) {
    auto result = std::map<int, std::string>();

    for (auto [key, value]: nonEncodedInfo) {
        result.insert(
                {key, getFileContent().at(key).substr(0, value.size())});
        fileNewContent.at(key) = fileNewContent.at(key)
                .substr(value.size(), fileNewContent.at(key).size() - value.size());
    }

    return result;
}

FReader* FReader::createReader() {
    FReader* result;

    println("Print path to file:");
    std::string path;
    std::string password;
    std::cin >> path;

    while (!isFileValid(path)) {
        println("Invalid file. Print path to file again:");
        std::cin >> path;
    }

    println("File valid. Print password for file:");
    std::cin >> password;

    return new FReader(path, password);
}