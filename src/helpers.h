
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
