/*
Author:     Abdl Fatiah
Date:       April, 2024
Purpose:    Defines the FileData class for scanning directories and compiling statistics on files,
            filtered by extension and user-defined criteria.
File:       FileData.h
*/

#ifndef FILEDATA_H
#define FILEDATA_H

#include "options.h"
#include <map>
#include <string>
#include <filesystem>
#include <regex>


#pragma once


struct FileStats {
    size_t count = 0;       
    size_t totalSize = 0;   
};

class FileData {
public:
    explicit FileData(const Options& options);
    void scanDirectory(); 
    const std::map<std::string, FileStats>& getFileStats() const;

private:
    Options options;
    std::map<std::string, FileStats> fileStats;

    void accumulateFileStats(const std::string& filename, size_t fileSize); 
    bool doesFileMatchFilter(const std::string& filename) const; 
};

#endif 
