#include "commands.h"
#include "commandUtils.h"
#include <vector>
#include <string>
#include <algorithm>

AddCategoryCommand::AddCategoryCommand(FReader* reader)
        : Command("addcat", "adds category",
                  "addcat <name>"
                                             ), reader(reader) { }

void AddCategoryCommand::run(std::vector<std::string> const& args) {
    if (args.size() < 1) {
        println("Not enough arguments. Type \"man addCat\" to get information about usage");
        return;
    }

    std::vector<std::string> categories = reader->getCategories();

    if (std::ranges::find(categories, args.at(0)) != categories.end()) {
        println("Category already added");
        return;
    }

    reader->addCategory(args.at(0));
    println("Category added");
}