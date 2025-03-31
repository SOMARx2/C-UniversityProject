#include "commands.h"
#include "commandUtils.h"
#include <vector>
#include <string>
#include <algorithm>

DeleteCategoryCommand::DeleteCategoryCommand(FReader* reader)
        : Command("deletecat",
                  "removes category and passwords with this category",
                  "deletecat <name>"), reader(reader) { }

void DeleteCategoryCommand::run(std::vector<std::string> const& args) {
    if (args.size() < 1) {
        println("Not enough arguments. Type man addCat to get information about usage");
        return;
    }

    std::vector<std::string> categories = reader->getCategories();

    if (std::ranges::find(categories, args.at(0)) == categories.end()) {
        println("Category not found");
        return;
    }

    int deletedPasswords = 0;
    std::vector<int> foundLines = reader->findValues(args.at(0), 2);

    reader->removeCategory(args.at(0));

    std::ranges::sort(foundLines, [](int f, int s) -> bool {
        return f > s;
    });

    for (int password : foundLines) {
        reader->removeLines(password - 2, 5);
        deletedPasswords++;
    }

    print("Category removed with");
    std::cout << deletedPasswords;
    println(" passwords");
}