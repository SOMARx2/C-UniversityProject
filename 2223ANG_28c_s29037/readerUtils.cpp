#include "readerUtils.h"

#include <string>
#include <vector>
#include <map>

void addNonEncoded(std::map<int, std::string> const& nonEncodedSaved, std::vector<std::string> &fileNewContent) {
    for (auto [key, value]: nonEncodedSaved) {
        if (key < fileNewContent.size()) {
            fileNewContent.at(key) = value + fileNewContent.at(key);
        } else {
            addElem(fileNewContent, value, key);
        }
    }
}

void deleteEmptySpaces(std::vector<std::string>& content) {
    for (int i = content.size() - 1; i > 0; i--) {
        if (content.at(i).empty()) {
            content.erase(content.begin() + i);
        } else {
            return;
        }
    }
}

std::string timeToString(int const &time) {
    if (time >= 0 && time < 10) {
        return "0" + std::to_string(time);
    } else {
        return std::to_string(time);
    }
}

std::string encrypt(std::string const &value, std::string const& key) {
    std::string result = "";

    if (key.size() == 0) {
        return value;
    }

    for (int i = 0; i < value.size(); i++) {
        result += (char)(value[i] + key.at(i % key.size()));
    }

    return result;
}

std::string decrypt(std::string const &value, std::string const &key) {
    std::string result;
    for (int i = 0; i < value.size(); i++) {
        result += (char) (value[i] - key.at(i % key.size()));
    }

    return result;
}

void addElem(std::vector<std::string> &vec,
                      std::string const &value, int const &position) {
    if (position < vec.size()) {
        vec.at(position) = value;
    } else {
        size_t sizeCopy = vec.size();

        for (int i = 0; i < position - sizeCopy; i++) {
            vec.push_back("");
        }

        vec.push_back(value);
    }
}

std::string numberToString(int value, int const& size) {
    std::string result;

    while (value > 0) {
        result = char('0' + value % 10) + result;
        value /= 10;
    }

    if (result.size() < size) {
        size_t resultSize = result.size();

        for (int i = 0; i < size - resultSize; i++) {
            result = '0' + result;
        }
    }

    return result;
}