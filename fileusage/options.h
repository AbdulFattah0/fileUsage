/*
Author:     Abdl Fatiah
Date:       April, 2024
Purpose:    Defines the Options class to parse and store command-line arguments for file analysis preferences,
            including help, sorting, filtering, and directory selection.
File:       Options.h
*/

#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>
#include <vector>
#include <regex>

using namespace std;

class Options {
public:
    bool help = false;                
    bool reverse = false;             
    bool sortBySize = false;          
    bool isRegexSet = false;          
    bool recursive = true;
    regex filterRegex;           
    string directory;            
    vector<string> args;    
    void printHelp() const; 
    // Constructor
    Options(int argc, char* argv[]);

private:
    
    void parseArguments(int argc, char* argv[]);
};

#endif // options.h