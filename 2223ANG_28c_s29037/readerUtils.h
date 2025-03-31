#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <map>

/**
 * This function modifies fileNewContent adding all nonEncodedInfo.
 *
 * @param nonEncodedSaved Map with indexes of lines and values on this lines.
 * @param fileNewContent Vector which should be modified.
 */
void addNonEncoded(std::map<int, std::string> const& nonEncodedSaved, std::vector<std::string> &fileNewContent);

/**
 * This function deletes all empty elements standing after last non empty element.
 *
 * @param content Vector which should be modified.
 */
void deleteEmptySpaces(std::vector<std::string>& content);

/**
 * This function transforms int to 2 sized string.
 * If int has 1 digit 0 would be added to begin.
 *
 * @param time Int representing time.
 * \returns String representing time.
 */
std::string timeToString(int const &time);

/**
 * This function encrypts string value corresponding to given password.
 *
 * @param value Value which should be encrypted.
 * @param key Password corresponding on which value will be encrypted.
 * \returns String representing encrypted value.
 */
std::string encrypt(std::string const &value, std::string const& key);

/**
 * This function decrypts string value corresponding to given password.
 *
 * @param value Value which should be decrypted.
 * @param key Password corresponding on which value will be decrypted.
 * \returns String representing decrypted value.
 */
std::string decrypt(std::string const &value, std::string const &key);

/**
 * This function adds element to vector.
 * If position bigger than size of vector it adds empty strings with value at the end.
 *
 * @param vec Vector which should be modified.
 * @param value Value which should be added.
 * @param position Where this value should be added.
 */
void addElem(std::vector<std::string> &vec,
                    std::string const &value, int const &position);

/**
 * This function adds element to vector.
 * If position bigger than size of vector it adds empty strings with value at the end.
 *
 * @param vec Vector which should be modified.
 * @param value Value which should be added.
 * @param position Where this value should be added.
 */
std::string numberToString(int value, int const& size);