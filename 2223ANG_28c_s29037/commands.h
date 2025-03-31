#pragma once
#include "reader.h"
#include <vector>
#include <string>

struct Command {
private:
    std::string commandName;
    std::string description;
    std::string usageDescription;

public:
    /**
    * \brief Creates new object representing Command.
    *
    * This function creates new object representing Command.
    *
    * @param commandName Name of command.
    * @param description Description of command.
    */
    Command(std::string commandName, std::string description, std::string usageDescription);

    /**
    * This function runs command.
    */
    virtual void run(std::vector<std::string> const &args);

    std::string const &getCommandName();
    std::string const &getDescription();
    std::string const &getUsageDescription();
};

struct ManCommand : Command {
private:
    std::vector<Command*> const& sessionCommands;

public:
    explicit ManCommand(std::vector<Command*> const& sessionCommands);

    void run(std::vector<std::string> const& args) override;
};

struct AddCommand : Command {
private:
    FReader* reader;
    std::vector<std::string> categories;

public:
    explicit AddCommand(FReader* reader);

    void run(std::vector<std::string> const& args) override;

private:
    bool checkCategory(std::string const& category);
};

struct SelectCommand : Command {
private:
    FReader* reader;
    int* selectedPassword;

public:
    SelectCommand(FReader* reader, int* selectedPassword);

    void run(std::vector<std::string> const& args) override;
};

struct SearchCommand : Command {
private:
    FReader* reader;

public:
    explicit SearchCommand(FReader* reader);

    void run(std::vector<std::string> const& args) override;
};

struct SortCommand : Command {
private:
    FReader* reader;

public:
    explicit SortCommand(FReader* reader);

    void run(std::vector<std::string> const& args) override;
};

struct EditCommand : Command {
private:
    FReader* reader;
    int* selectedPassword;

public:
    EditCommand(FReader* reader, int* selectedPassword);

    void run(std::vector<std::string> const& args) override;
};

struct DeleteCommand : Command {
private:
    FReader* reader;
    int* selectedPassword;

public:
    DeleteCommand(FReader* reader, int* selectedPassword);

    void run(std::vector<std::string> const& args) override;
};

struct AddCategoryCommand : Command {
private:
    FReader* reader;

public:
    explicit AddCategoryCommand(FReader* reader);

    void run(std::vector<std::string> const& args) override;
};

struct DeleteCategoryCommand : Command {
private:
    FReader* reader;

public:
    explicit DeleteCategoryCommand(FReader* reader);

    void run(std::vector<std::string> const& args) override;
};

struct PrintCategoryCommand : Command {
private:
    FReader* reader;

public:
    explicit PrintCategoryCommand(FReader* reader);

    void run(std::vector<std::string> const& args) override;
};