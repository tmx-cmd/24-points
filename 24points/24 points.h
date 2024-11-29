#pragma once
#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<cmath>
#include<cstdlib>
#include<string>
#include<list>
#include <forward_list>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include <array>
#include <regex>
#include<random>
#include<stdexcept>
using namespace std;
double calculate(string a);
// error() simply disguises throws:
inline void error(const string& s) {
    throw runtime_error(s);
}

inline void error(const string& s, const string& s2) {
    error(s + s2);
}

inline void error(const string& s, int i) {
    ostringstream os;
    os << s << ": " << i;
    error(os.str());
}

// error function to be used (only) until error() is introduced in Chapter 5:
inline void simple_error(string s) {  // write ``error: s and exit program
    cerr << "error: " << s << '\n';
    exit(1);
}