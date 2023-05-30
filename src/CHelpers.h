
#pragma once

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int getUserOption(int maxChoice);

string & loadString(string &loadedString, bool emptyCheck=true);

vector<string> &loadMultiString(vector<string> &storeVec, const string &propertyName, int maxNum);

void convertStringLowercase(string &toConv);

int loadNumber(int minNum, int maxNum);

string addZeroPadding(size_t num);

ostream &printSeparator(ostream &out, int type=0);

ostream &printVector(ostream &out, const vector<string> &vec);

string stringifyDay(size_t year, size_t month, size_t day);
