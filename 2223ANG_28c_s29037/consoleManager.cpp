#include "consoleManager.h"
#include "commandUtils.h"
#include "reader.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

ConsoleManager::ConsoleManager(FReader* reader) : reader(reader) {
    selectedPassword = -1;
    setCommands();
    bool isCommandFound = false;
    bool isBracesClosed = true;

    println("Session started. Print man command to get list of commands:");

    std::string line;

    while (true) {
        getline(std::cin, line);
        auto commandStream = std::stringstream(line);

        std::string command;
        std::vector<std::string> args;
        commandStream >> command;

        for (std::string arg; commandStream >> arg; ) {
            if (arg.at(0) != '\"') {
                args.push_back(arg);
            } else {
                std::string whiteArg = arg + " ";

                while (arg.at(arg.size() - 1) != '\"' && isBracesClosed) {
                    if (commandStream >> arg) {
                        whiteArg += arg + " ";
                    } else {
                        println("Open braces was not closed");
                        isBracesClosed = false;
                    }
                }

                args.push_back(whiteArg.substr(1, whiteArg.size() - 3));
            }
        }

        if (isBracesClosed) {
            for (Command *sessionCommand: commands) {
                if (sessionCommand->getCommandName() == command) {
                    sessionCommand->run(args);
                    isCommandFound = true;
                }
            }
        }

        if (command == "exit") {
            println("Finishing work");
            return;
        }

        if (!isCommandFound && line != "" && isBracesClosed) {
            println("Command not found");
        } else {
            isCommandFound = false;
        }

        isBracesClosed = true;
    }
}

void ConsoleManager::setCommands() {
    commands.push_back(new ManCommand(commands));
    commands.push_back(new AddCommand(reader));
    commands.push_back(new SelectCommand(reader, &selectedPassword));
    commands.push_back(new SearchCommand(reader));
    commands.push_back(new SortCommand(reader));
    commands.push_back(new EditCommand(reader, &selectedPassword));
    commands.push_back(new DeleteCommand(reader, &selectedPassword));
    commands.push_back(new AddCategoryCommand(reader));
    commands.push_back(new DeleteCategoryCommand(reader));
    commands.push_back(new PrintCategoryCommand(reader));
}