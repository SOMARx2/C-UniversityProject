#pragma once
#include <vector>
#include <string>
#include "reader.h"
#include "commands.h"

class ConsoleManager {
private:
    std::vector<Command*> commands;
    FReader* reader;
    std::vector<std::string> categories;
    int selectedPassword;

public:
    /**
    * \brief Creates new object representing ConsoleManager.
    *
    * This function creates new object representing ConsoleManager.
    *
    * @param reader Reader class with which ConsoleManager will work.
    */
    explicit ConsoleManager(FReader* reader);

private:
    /**
    * This function adds default commands of ConsoleManager.
    */
    void setCommands();
};