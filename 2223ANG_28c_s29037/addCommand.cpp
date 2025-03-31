#include "commands.h"
#include "commandUtils.h"
#include <vector>
#include <string>
#include <algorithm>

AddCommand::AddCommand(FReader* reader)
        : Command("addpass", "adds password",
                  "This command has several variants:\n"
                  " addpass <name> <password> <category>\n"
                  " addpass <name> <password> <category> -w <website>\n"
                  " addpass <name> <password> <category> -l <login>\n"
                  " addpass <name> <password> <category> <website> <login>\n"
                  "Generate password variants:\n"
                  " addpass <name> -g <#passwordsize> <?hasLetters> <?hasSpecialSymbol> <category>\n"
                  " addpass <name> -g <#passwordsize> <?hasLetters> <?hasSpecialSymbol> <category> -w <website>\n"
                  " addpass <name> -g <#passwordsize> <?hasLetters> <?hasSpecialSymbol> <category> -l <login>\n"
                  " addpass <name> -g <#passwordsize> <?hasLetters> <?hasSpecialSymbol> <category> <website> <login>"
                  ), reader(reader) { }

void AddCommand::run(std::vector<std::string> const& args) {
    if (args.size() < 3) {
        println("Not enough arguments. Type \"man addpass\" to get information about usage");
        return;
    }

    if (args.size() == 3) {
        if (!checkCategory(args.at(2))) {
            return;
        }

        reader->addLines({args.at(0), args.at(1), args.at(2), "", ""});
        println("added new password");
        return;
    }

    if (args.at(1) == "-g") {
        if (args.size() < 5 || args.size() == 6) {
            println("Not enough arguments. Type: \"man addpass\" to get information about usage");
            return;
        }

        if (!isNum(args.at(2))) {
            println("3rd argument should be positive integer value. Type: \"man addpass\" to get information about usage");
            return;
        }

        if (!isBool(args.at(3)) || !isBool(args.at(4))) {
            println("4th and 5th arguments should be boolean value. Type: \"man addpass\" to get information about usage");
            return;
        }

        if (!checkCategory(args.at(5))) {
            return;
        }

        std::string website;
        std::string login;

        if (args.size() > 7) {
            setWebsiteLogin(args.at(6), args.at(7), website, login);
        }

        reader->addLines({args.at(0),
                          generatePassword(
                                  stringToInt(args.at(2)),
                                  stringToBool(args.at(3)),
                                  stringToBool(args.at(4))
                          ), args.at(5), website, login});
        println("added new password");
        return;
    }

    if (args.size() == 4) {
        println("Not enough arguments. Type: \"man addpass\" to get information about usage");
        return;
    }

    if (!checkCategory(args.at(2))) {
        return;
    }

    std::string website;
    std::string login;

    if (args.size() > 4) {
        setWebsiteLogin(args.at(3), args.at(4), website, login);
    }

    reader->addLines({args.at(0), args.at(1), args.at(2), website, login});
    println("added new password");
}

bool AddCommand::checkCategory(std::string const &category) {
    std::vector<std::string> fileCategories = reader->getCategories();

    if (std::ranges::find(fileCategories, category) == fileCategories.end()) {
        std::string answer;
        println("This category does not exist. Add new category y/n?");
        std::cin >> answer;

        if (answer != "y") {
            println("Creation cancelled");
            return false;
        }

        reader->addCategory(category);
    }

    return true;
}