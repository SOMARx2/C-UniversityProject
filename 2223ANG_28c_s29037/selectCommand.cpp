#include "commands.h"
#include "commandUtils.h"
#include <vector>
#include <string>

SelectCommand::SelectCommand(FReader* reader, int* selectedPassword)
        : Command("selectpass", "selects password",
                  "selectpass <#parameterId> <value>"
                  ), reader(reader), selectedPassword(selectedPassword) { }

void SelectCommand::run(std::vector<std::string> const &args) {
    if (args.size() < 2) {
        println("Not enough arguments. Type: \"man selectpass\" to get information about usage");
        return;
    }

    int parameterId = getParameter(args.at(0));

    if (parameterId == -1) {
        println("Type: \"man selectpass\" to get information about usage");
        return;
    }

    std::vector<int> foundLines = reader->findValues(args.at(1), parameterId);

    if (foundLines.size() == 0) {
        println("No passwords with this parameter found. Type: \"man selectpass\" to get information about usage");
        return;
    }

    if (foundLines.size() > 1) {
        println("Several passwords found. Type id of password printed below");

        for (int i = 0; i < foundLines.size(); i++) {
            std::cout << i + 1 << ":\n";
            printPassword(reader->getInfo(foundLines.at(i)));
            std::cout << "\n";
        }

        int passwordId;
        std::cin >> passwordId;
        passwordId--;

        if (passwordId >= foundLines.size() || passwordId < 0) {
            println("No password with such id found. Selection cancelled");
            return;
        }

        *selectedPassword = foundLines.at(passwordId) - parameterId;
        println("Password selected");
        return;
    }

    *selectedPassword = foundLines.at(0) - parameterId;
    println("Password selected");
    return;
}