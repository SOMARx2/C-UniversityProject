#include "commands.h"
#include <utility>
#include <vector>
#include <string>

Command::Command(std::string commandName, std::string description, std::string usageDescription)
        : commandName(std::move(commandName)),
        description(std::move(description)),
        usageDescription(std::move(usageDescription)) {}

void Command::run(std::vector<std::string> const &args) {}

std::string const &Command::getCommandName() {
    return commandName;
}

std::string const &Command::getDescription() {
    return description;
}

std::string const &Command::getUsageDescription() {
    return usageDescription;
}