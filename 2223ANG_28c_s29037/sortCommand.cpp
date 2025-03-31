#include "commands.h"
#include "commandUtils.h"
#include <vector>
#include <string>
#include <algorithm>

SortCommand::SortCommand(FReader* reader)
        : Command("sortpass", "prints passwords sorted by parameters",
                  "This command has 3 variants:\n"
                  "\n"
                  "Sorts by creation time:\n"
                  " sortpass\n"
                  "Sorts by parameter:\n"
                  " sortpass <#parameterId>\n"
                  "Sorts by 2 parameters:\n"
                  " sortpass <#parameterId> <parameterId>"
                ), reader(std::move(reader)) { }

        // sortpass <parameterId> <parameterId>
void SortCommand::run(std::vector<std::string> const &args) {
    if (args.size() == 0) {
        if (reader->getPasswordSize() == 0) {
            println("File is empty");
            return;
        }

        for (int i = 0; i < reader->getPasswordSize(); i++) {
            std::cout << i + 1 << ":\n";
            printPassword(reader->getInfo(i * 5));
            println("");
        }
        return;
    }

    int parameterId = getParameter(args.at(0));

    if (parameterId == -1) {
        println("Type: \"man sortpassword\" to get information about usage");
        return;
    }

    int secondParameterId = 1;

    if (args.size() > 1) {
        secondParameterId = getParameter(args.at(1));

        if (secondParameterId == -1) {
            println("Type: \"man sortpassword\" to get information about usage");
            return;
        }
    }

    if (reader->getPasswordSize() == 0) {
        println("File is empty");
        return;
    }

    std::vector<std::vector<std::string>> passwords = reader->getAllPasswords();

    std::ranges::sort(passwords, [parameterId, secondParameterId](std::vector<std::string> const& pass,
                                                                  std::vector<std::string> const& pass1) -> bool {

        if (pass.at(parameterId) == pass1.at(parameterId)) {
            return pass.at(secondParameterId) < pass1.at(secondParameterId);
        } else {
            return pass.at(parameterId) < pass1.at(parameterId);
        }
    });

    for (auto password : passwords) {
        printPassword(password);
        std::cout << "\n";
    }
}