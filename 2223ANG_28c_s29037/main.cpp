#include "consoleManager.h"
#include "reader.h"

int main() {
    FReader* reader = FReader::createReader();
    ConsoleManager consoleManager = ConsoleManager(reader);
}

