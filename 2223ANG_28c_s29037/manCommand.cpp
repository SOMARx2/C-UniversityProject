#include "commands.h"
#include "commandUtils.h"
#include <vector>
#include <string>

ManCommand::ManCommand(std::vector<Command*> const& sessionCommands)
        : Command("man", "shows command list and their descriptions",
                  "man <name>"
                  ), sessionCommands(sessionCommands) { }

void ManCommand::run(std::vector<std::string> const &args) {
    if (args.empty()) {
        println("Type \"man <command name>\" to get more information about command usage.\n"
                "\n"
                "In command usage description arguments are written in <> with name of argument inside\n"
                "\n"
                "If argument name starts from # that mean that only integer value accepted\n"
                "If argument name starts from ? that mean that only boolean value accepted\n"
                "\n"
                "If argument name is \"parameterId\" that mean that integer value from 1 to 5 should be written\n"
                "meaning one of components of the password:\n"
                "1 - Name, 2 - password, 3 - category, 4 - website, 5 - login\n"
                "\n"
                "To type argument with spaces, \" should be used\n"
                );

        for (auto command: sessionCommands) {
            println(command->getCommandName() + ": " + command->getDescription());
        }

        return;
    }

    for (auto command: sessionCommands) {
        if (command->getCommandName() == args.at(0)) {
            println(command->getUsageDescription());
            return;
        }
    }

    println("Command not found");
}