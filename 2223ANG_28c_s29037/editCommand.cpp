#include "commands.h"
#include "commandUtils.h"

EditCommand::EditCommand(FReader* reader, int* selectedPassword)
        : Command("editpass", "edits password",
                  " editpass <#parameterId> <value>\n"
                  "To use this variant, password should be selected first\n"
                  " editpass"
                  ), reader(reader), selectedPassword(selectedPassword) {

}

void EditCommand::run(std::vector<std::string> const& args) {
    if (args.size() < 2) {
        println("Not enough arguments");
        println("Type: \"man editpass\" to get information about usage");
        return;
    }

    if (args.size() == 3) {
        println("Not enough arguments");
        println("Type: \"man editpass\" to get information about usage");
        return;
    }

    int parameterId = getParameter(args.at(0));

    if (parameterId == -1) {
        println("Type: \"man editpass\" to get information about usage");
        return;
    }

    if (args.size() > 3) {
        int secondParameter = getParameter(args.at(2));

        if (secondParameter == -1) {
            println("Type: \"man editpass\" to get information about usage");
            return;
        }

        std::vector<int> foundLines = reader->findValues(args.at(1), parameterId);

        if (foundLines.empty()) {
            println("No such passwords found");
            return;
        }

        for (int line : foundLines) {
            reader->setValueInLine((line - parameterId) + secondParameter, args.at(3), true);
        }

        std::cout << foundLines.size() << " passwords changed\n";
        return;
    }

    if (*selectedPassword == -1) {
        println("password not selected");
        println("Type: \"man editpass\" to get information about usage");
        return;
    }

    reader->setValueInLine(*selectedPassword + parameterId, args.at(1), true);
    println("password changed");
}