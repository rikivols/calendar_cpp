
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

int getUserOption(int maxChoice);

string & loadString(string &loadedString, bool allowEmpty=false);

vector<string> &loadMultiString(vector<string> &storeVec, const string &propertyName, int maxNum);

void convertStringLowercase(string &toConv);

int loadNumber(int minNum, int maxNum);

string addZeroPadding(int num);

ostream &printSeparator(ostream &out, char separator='-');

ostream &printVector(ostream &out, const vector<string> &vec);

string &stripString(string & inp);

string exportFormatVector(const vector<string> &vec);

tm *getTimeNow();

void splitString(vector<string> &result, const string &line, char separator);

int convertStringToInt(const string &inp);

bool loadYesNo(const string &message);

bool isInVector(const vector<string> &vec1, const vector<string> &vec2);
