#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <map>

template<typename key, typename value>
key getKey(std::map<key, value> const &map, value const& valueToFind);
bool isFileValid(std::string const &path);

class FReader {
private:
    std::map<int, std::string> nonEncodedInfo;
    std::string file;
    std::string password;

public:
    /**
     * \brief Creates object of class reader.
     *
     * Creates object of class reader which can manage file with passwords.
     *
     * @param file file with passwords.
     * @param password passwords to open encrypted file.
     */
    explicit FReader(std::string file, std::string password);

    /**
     * \brief Inserts new lines to file.
     *
     * This function inserts before categories and encrypts lines.
     * From lines vector to file.
     *
     * @param lines Vector of lines which will be inserted.
     */
    void addLines(std::vector<std::string> const& lines);

    /**
     * \brief Finds values corresponding to parameter.
     *
     * This function searches in file for passwords with corresponding parameter.
     *
     * @param value Value which should be founded.
     * @param parameterId Parameter id.
     * \return Lines numbers where values was founded.
     */
    std::vector<int> findValues(std::string const &value, int const &parameterId);

    /**
     * \brief Finds all information about password.
     *
     * This function finds all information about file.
     *
     * @param line Line where password located.
     * \return 5 sized vector with all information.
     */
    std::vector<std::string> getInfo(int line);

    /**
     * \brief Removes lines from file.
     *
     * This function removes some lines from file.
     * It doesn't removes values nonEncodedInfo map.
     *
     * @param from First line which should be removed.
     * @param size Quantity consecutive lines which should be removed in total.
     * @param isUpdateCounter Whether update counter corresponding for passwords length in file
     */
    void removeLines(int const &from, int const &size, bool const& isUpdateCounter = true);

    /**
     * \brief Inserts value to file.
     *
     * This function adds line to file.
     *
     * @param from Line where value should be inserted.
     * @param value Value which should be inserted.
     * @param isEncrypt Whether encrypt value which should be inserted.
     */
    void insertValue(int const &line, std::string const &value, bool isEncrypt = false);

    /**
     * \brief Sets value to line.
     *
     * This function replaces whole line except nonEncodedInfo with new value.
     * If nonEncodedInfo met, it places new value after nonEncodedInfo.
     *
     * @param line Line where value should be replaced.
     * @param value Value which should be set it line.
     * @param isEncrypt Whether encrypt value which should be set.
     */
    void setValueInLine(int const &line, std::string const &value, bool isEncode = false);

    /**
     * \brief Finds and returns all passwords.
     *
     * This function searches for all passwords and return them.
     *
     * \return Vector of 5 sized vectors each represents password.
     */
    std::vector<std::vector<std::string>> getAllPasswords();

    /**
     * This function counts quantity of written passwords.
     *
     * \return Quantity of passwords.
     */
    int getPasswordSize();

    /**
     * \brief Removes category.
     *
     * Removes field from file corresponding to given category.
     *
     * @param category Name of category.
     */
    void removeCategory(std::string category);

    /**
     * \brief Adds category.
     *
     * Adds field to file which represents category.
     *
     * @param category Name of category.
     */
    void addCategory(std::string category);

    /**
     * \brief Searches for categories.
     *
     * This function searches for all categories in file.
     *
     * \return Vector of all category names.
     */
    std::vector<std::string> getCategories();

    /**
     * \brief Creates reader object.
     *
     * This function creates reader object depending on requested arguments from console.
     *
     * \return Created reader object.
     */
    static FReader *createReader();

private:
    /**
     * This function returns how many space is taken by passwords.
     *
     * \return How many space is taken by passwords.
     */
    size_t getSize();

    /**
     * This function returns how many space is taken by categories.
     *
     * \return How many space is taken by categories.
     */
    size_t getCategorySize();

    /**
     * \breif Rewrites content of file.
     *
     * This function rewrites whole file with new content.
     *
     * @param content Vector of new lines representing new content.
     */
    void setFileContent(std::vector<std::string> const &content);

    /**
     * This function returns all lines.
     *
     * \returns Vector of lines from file.
     */
    std::vector<std::string> getFileContent();

    /**
     * This function overrides content of file.
     * NonEncodedInfo can be also overwritten.
     *
     * @param line Line where data should be overwritten.
     * @param line Value to which overwrites line.
     */
    void overrideValueInLine(int const &line, std::string const &value);

    /**
     * This function sets current time in file.
     */
    void setCurrentTime();

    /**
     * This function modifies fileNewContent deleting all nonEncodedInfo.
     *
     * @param fileNewContent Vector which should be modified.
     * \return All data which was written.
     */
    std::map<int, std::string> removeNonEncoded(std::vector<std::string> &fileNewContent);
};
