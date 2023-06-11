/**
 * Help functions for various classes
 */

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

/**
 * Prompts user to select a given option.
 *
 * @param maxChoice max option he can pick.
 * @return option picked by the user
 */
int getUserOption(int maxChoice);

/**
 * Gets string from a user's input.
 *
 * @param loadedString string to save the user's input to
 * @param allowEmpty whether we allow an empty option
 * @return string inputted by the user
 */
string &loadString(string &loadedString, bool allowEmpty=false);

/**
 * Loads vector from a user.
 *
 * @param storeVec vector to store the input to
 * @param propertyName name of the vector's property we're loading
 * @param maxNum max number of vector's elements
 * @return
 */
vector<string> &loadMultiString(vector<string> &storeVec, const string &propertyName, int maxNum);

void convertStringLowercase(string &toConv);

/**
 * Loads a number from the user's input
 *
 * @param minNum min number user can select
 * @param maxNum max num user can select
 * @return loaded user's number
 */
int loadNumber(int minNum, int maxNum);

/**
 * Converts number to string and gives 0 at the start if it's only 1 digit
 *
 * @param num number to convert
 * @return string number with padding
 */
string addZeroPadding(int num);

/**
 * Stores the given value n times to ostream.
 *
 * @param out ostream to modify
 * @param separator separator to store
 * @return modified ostream
 */
ostream &printSeparator(ostream &out, char separator='-');

/**
 * Stores a vector element to ostream
 *
 * @param out ostream to modify
 * @param vec vector to store/print
 * @return modified ostream
 */
ostream &printVector(ostream &out, const vector<string> &vec);

/**
 * Remove all space character from string's suffix and prefix. Models Python's strip function.
 *
 * @param inp string to strip
 * @return stripped string.
 */
string &stripString(string & inp);

/**
 * Export a vector element
 *
 * @param vec vector to export
 * @return exported calendar's event
 */
string exportFormatVector(const vector<string> &vec);

tm *getTimeNow();


/**
 * Splits string to a vector by the given separator.
 *
 * @param result final vector
 * @param line string to split
 * @param separator separator to split the string by
 */
void splitString(vector<string> &result, const string &line, char separator);

/**
 * Converts string to integer, returns -1 if fails.
 *
 * @param inp string to convert
 * @return converted string to integer
 */
int convertStringToInt(const string &inp);

/**
 * Loads from the user yes/no option.
 *
 * @param message message to display to the user.
 * @return yes = true, no = false
 */
bool loadYesNo(const string &message);

/**
 * Checks if whole vec1 is in vec2
 *
 * @param vec1 vector that should be in vec2
 * @param vec2 vector to compare against
 * @return true = is in, false = isn't
 */
bool isInVector(const vector<string> &vec1, const vector<string> &vec2);
