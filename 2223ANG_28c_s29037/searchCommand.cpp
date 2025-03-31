#include "commands.h"
#include "commandUtils.h"
#include <vector>
#include <string>

SearchCommand::SearchCommand(FReader* reader)
        : Command("searchpass", "searches for passwords with parameter",
                  "searchpass <#parameterId> <value>"
                  ), reader(reader) { }

// select <parameterId> <value>
void SearchCommand::run(std::vector<std::string> const &args) {
    if (args.size() < 2) {
        println("Not enough arguments. Type: \"man searchpass\" to get information about usage");
        return;
    }

    int parameterId = getParameter(args.at(0));

    if (parameterId == -1) {
        println("Type: \"man searchpass\" to get information about usage");
        return;
    }

    std::vector<int> foundLines = reader->findValues(args.at(1), parameterId);

    if (foundLines.size() == 0) {
        println("No passwords with this parameter found.");
        return;
    }

    if (foundLines.size() > 1) {
        std::cout << foundLines.size();
        println(" passwords found");

        for (int i = 0; i < foundLines.size(); i++) {
            std::cout << i + 1 << ":\n";
            printPassword(reader->getInfo(foundLines.at(i)));
            println("");
        }

        return;
    }

    println("1 password found\n");
    printPassword(reader->getInfo(foundLines.at(0)));
    println("");
}