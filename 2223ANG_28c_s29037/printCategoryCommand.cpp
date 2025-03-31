#include "commands.h"
#include "commandUtils.h"
#include <vector>
#include <string>

PrintCategoryCommand::PrintCategoryCommand(FReader* reader)
        : Command("printcat", "prints all categories",
                  "printcat"
                  ), reader(reader) { }

void PrintCategoryCommand::run(std::vector<std::string> const& args) {
    std::vector<std::string> categories = reader->getCategories();

    if (categories.size() == 0) {
        println("No categories found");
        return;
    }

    for (auto category : categories) {
        println(category);
    }
}