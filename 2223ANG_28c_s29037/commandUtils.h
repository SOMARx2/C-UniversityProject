#pragma once
#include <iostream>
#include <vector>

/**
 * \brief This function prints given vector of strings.
 *
 * This function prints vector of strings separated by separator.
 *
 * @param obj Vector of strings which should be printed.
 * @param separator Separator which separates all printed strings.
 */
void print(std::vector<std::string> const &obj, std::string const &separator = " ");

/**
 *
 * \brief This function prints given string.
 * This function prints string with separator.
 *
 * @param obj String which should be printed.
 * @param separator Separator which will be added to printed strings.
 */
void print(std::string const &obj, std::string const &separator = " ");

/**
 * \brief This function prints given vector of strings.
 *
 * This function prints vector of strings separated by separator and adding new line at the end.
 *
 * @param obj Vector of strings which should be printed.
 * @param separator Separator which separates all printed strings.
 */
void println(std::vector<std::string> const &obj);

/**
 * \brief This function prints given string.
 *
 * This function prints string added with separator and adding new line at the end.
 *
 * @param obj String which should be printed.
 * @param separator Separator which separates all printed strings.
 */
void println(std::string const &obj);

/**
 * \brief Modifies website and login fields depending on firstArg and secondArg.
 *
 * This function modifies website and login fields depending on firstArg and secondArg.
 *
 * If firstArg equal to -w website will be changed to secondArg.
 * If firstArg equal to -l login will be changed to secondArg.
 * Otherwise website will be changed to firstArg and login will be changed to secondArg.
 *
 * @param firstArg FirstArgument.
 * @param secondArg SecondArgument.
 * @param website Website string which should be modified.
 * @param login Login string which should be modified.
 */
void setWebsiteLogin(std::string const &firstArg, std::string const &secondArg,
                     std::string &website, std::string &login);

/**
 * \brief Checks whether char is digit.
 *
 * This function checks whether given char is digit.
 *
 * @param value Value which should be checked.
 * \return Whether char is digit.
 */
bool isNum(char const& value);

/**
 * \brief Checks whether string is number.
 *
 * This function checks whether given string can be represented as positive integer value.
 *
 * @param value Value which should be checked.
 * \return Whether string is number.
 */
bool isNum(std::string const& value);

/**
 * \brief Checks whether string is boolean.
 *
 * This function checks whether given string can be represented as boolean value.
 *
 * @param value Value which should be checked.
 * \return Whether string is boolean.
 */
bool isBool(std::string const& value);

/**
 * \brief Converts given string to int.
 *
 * This function converts given string to int.
 * Functions assumes that given string is fully consist of digits.
 *
 * @param value Value which should be converted.
 * \return Integer converted from given string.
 */
int stringToInt(std::string value);

/**
 * \brief Converts given string to boolean.
 *
 * This function converts given string to boolean.
 * Functions assumes that given string can be represented as boolean.
 *
 * @param value Value which should be converted.
 * \return Boolean converted from given string.
 */
bool stringToBool(std::string const& value);

/**
 * \brief Checks whether char is letter.
 *
 * This function checks whether given char is letter.
 *
 * @param value Value which should be checked.
 * \return Whether char is letter.
 */
bool isLetter(char const& value);

/**
 * \brief Checks whether char is special symbol.
 *
 * This function checks whether given char is special symbol.
 *
 * @param value Value which should be checked.
 * \return Whether char is special symbol.
 */
bool isSpecialSymbol(char const& value);

/**
 * \brief Prints password.
 *
 * This function prints given password appending with names of parameters.
 *
 * @param password Password which should be printed.
 */
void printPassword(std::vector<std::string> const& password);

/**
 * \brief Generates new password.
 *
 * This function generates new password.
 *
 * @param charNum How many chars will have password.
 * @param isLetterIncluded Whether letters should be included in password.
 * @param isSpecialCharIncluded Whether special characters should be included in password.
 * \return Generated password
 */
std::string generatePassword(int const &charNum, bool const &isLetterIncluded, bool const &isSpecialCharIncluded);

/**
 * \brief Converts string to number from 1 to 5.
 *
 * This function converts string to number from 1 to 5.
 *
 * @param parameter Value which should be converted.
 * \return Number from 1 to 5 or -1 if string can't be represented as digit from 1 to 5.
 */
int getParameter(std::string const& parameter);