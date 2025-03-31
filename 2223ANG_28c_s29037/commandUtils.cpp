#include "commandUtils.h"
#include <vector>
#include <string>
#include <cmath>

void print(std::vector<std::string>
           const &obj,
           std::string const &separator) {

    for (const auto &i: obj) {
        std::cout << i;
        std::cout << separator;
    }
}

void print(std::string const &obj, std::string const &separator) {
    std::cout << obj;
    std::cout << separator;
}

void println(std::vector<std::string> const &obj) {
    print(obj);
    std::cout << "\n";
}

void println(std::string const &obj) {
    print(obj);
    std::cout << "\n";
}

void setWebsiteLogin(std::string const &firstArg, std::string const &secondArg,
                              std::string &website, std::string &login) {
    if (firstArg == "-w") {
        website = secondArg;
    } else if (firstArg == "-l") {
        login = secondArg;
    } else {
        website = firstArg;
        login = secondArg;
    }
}

bool isNum(char const& value) {
    return value >= '0' && value <= '9';
}

bool isNum(std::string const& value) {
    for (auto symbol: value) {
        if (symbol < '0' || symbol > '9') {
            return false;
        }
    }

    return true;
}

bool isBool(std::string const& value) {
    return value == "true" || value == "false";
}

int stringToInt(std::string value) {
    int result = 0;

    for (int i = 0; i < value.size(); i++) {
        result += (int)(value[i] - '0') * pow(10, value.size() - i - 1);
    }

    return result;
}

bool stringToBool(std::string const& value) {
    return value == "true";
}

bool isLetter(char const& value) {
    return (value >= 'A' && value <= 'Z') || (value >= 'a' && value <= 'z');
}

bool isSpecialSymbol(char const& value) {
    return value >= '!' && value <= '&';
}

void printPassword(std::vector<std::string> const& password) {
    for (int i = 0; i < password.size(); i++) {
        if (!password.at(i).empty()) {
            switch (i) {
                case 0:
                    print("Name:");
                    break;
                case 1:
                    print("Password:");
                    break;
                case 2:
                    print("Category:");
                    break;
                case 3:
                    print("Website:");
                    break;
                case 4:
                    print("Login:");
                    break;
            }

            println(password.at(i));
        }
    }
}

std::string generatePassword(int const &charNum, bool const &isLetterIncluded, bool const &isSpecialCharIncluded) {
    std::string result;

    for (int i = 0; i < charNum; i++) {
        char symbol = (char) ((rand() % 89) + 33);

        while (!isNum(symbol)
               && (!isLetter(symbol) || !isLetterIncluded)
               && (!isSpecialSymbol(symbol) || !isSpecialCharIncluded)) {

            symbol = (char) ((rand() % 89) + 33);
        }

        result += symbol;
    }

    return result;
}

int getParameter(std::string const& parameter) {
    if (!isNum(parameter)) {
        println("One of arguments should be positive integer");
        return -1;
    }

    int parameterId = stringToInt(parameter);

    if (parameterId > 5 || parameterId < 1) {
        println("One of arguments should be less than 6 and more than 0");
        return -1;
    }

    parameterId--;

    return parameterId;
}