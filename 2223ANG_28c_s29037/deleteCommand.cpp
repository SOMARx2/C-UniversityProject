#include "commands.h"
#include "commandUtils.h"

DeleteCommand::DeleteCommand(FReader* reader, int* selectedPassword)
        : Command("deletepass", "deletes password",
                  " deletepass <#parameterId> <value>\n"
                  "To use this variant, password should be selected first\n"
                  " deletepass"
                  ), reader(reader), selectedPassword(selectedPassword) { }

void DeleteCommand::run(std::vector<std::string> const& args) {
    if (args.empty()) {
        if (*selectedPassword == -1) {
            println("Not enough arguments or password not selected");
            println("Type: \"man deletepass\" to get information about usage");
            return;
        }

        reader->removeLines(*selectedPassword, 5);
        *selectedPassword = -1;
        println("password deleted");
        return;
    }

    int parameterId = getParameter(args.at(0));

    if (parameterId == -1) {
        println("Type: \"man deletepass\" to get information about usage");
        return;
    }

    std::vector<int> foundLines = reader->findValues(args.at(1), parameterId);

    if (foundLines.empty()) {
        println("No such passwords found");
        return;
    }

    for (int line : foundLines) {
        reader->removeLines(line - parameterId, 5);
    }

    *selectedPassword = -1;
    std::cout << foundLines.size() << " passwords deleted\n";
}