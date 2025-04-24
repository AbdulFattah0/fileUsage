/*
Author:     Abdl Fatiah
Date:       April, 2024
Purpose:    The main entry point for a file analysis application. This program processes command-line arguments to determine user preferences
            for file scanning, including help directives, recursive scanning, sorting by size or name, reverse sorting, and regex filtering.
            It leverages the Options, FileData, and PrintReport classes to scan the specified directory (or current directory by default),
            compile statistics on file sizes and counts by extension, and then print a formatted report based on the user's options.
File:       main.cpp 
*/

#include "options.h"
#include "filedata.h"
#include "printreport.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    Options options(argc, argv); 

    if (options.help) {
        options.printHelp(); 
        return 0;
    }

    // Initialize file data processing and reporting
    FileData fileData(options);
    fileData.scanDirectory(); // Scan the directory based on provided options
    PrintReport report(fileData.getFileStats(), options);
    report.execute(); // Generate and display the report

    return 0;
}
