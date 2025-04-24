/*
Author:     Abdl Fatiah
Date:       April, 2024
Purpose:    Implements the PrintReport class for formatting and displaying file statistics based on user options.
            It processes and presents data on file counts and sizes by extension.

File:       PrintReport.h
*/
#pragma once
#include "filedata.h" 
#include "options.h"

class PrintReport {
public:
    PrintReport(const std::map<std::string, FileStats>& fileStats, const Options& options);
    void execute();

private:
    const std::map<std::string, FileStats>& fileStats;
    const Options& options;
};