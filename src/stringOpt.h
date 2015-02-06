#ifndef STRINGOPT_H
#define STRINGOPT_H

#include <string>
#include <vector>
#include <cctype>
#include <string>
#include <iostream>
#include <sys/stat.h>

using namespace std;

string Ltrim(const string&);
string Rtrim(const string&);
string trim(const string&);

int separateWord(vector<string>&, string);

void addsuffix(string&, char);
string chgsuffix(const string&, const string&);
string getsuffix(const string& nm);

string toUpper(const string&);
string toLower(const string&);

long getFileSize(const string&);

#endif
