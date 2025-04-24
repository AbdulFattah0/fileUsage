#include "filedata.h"
#include <iostream>
#include <filesystem>
#include<regex>

namespace fs = std::filesystem;


// Constructor
FileData::FileData(const Options& options) : options(options) {}

/*
* fn: processEntries
* brief: Processes each filesystem entry within the given range,
* updating file statistics for each file's extension if it meets the filtering criteria.
* param: begin - Iterator to the start of the filesystem entries.
*        end - Iterator to the end of the filesystem entries.
*        options - Options object containing user-defined criteria, such as regex filtering.
*        fileStats - Map to accumulate statistics about files, keyed by file extension.
* return: void - This function does not return a value but modifies the fileStats map in-place.
*/
template<typename T>
void processEntries(T begin, T end, const Options& options, std::map<std::string, FileStats>& fileStats) {
    for (auto it = begin; it != end; ++it) {
        const auto& entry = *it;
        if (!is_regular_file(entry.status())) continue; // Skip if not a regular file

        std::string filename = entry.path().filename().string();
        if (options.isRegexSet && !std::regex_match(filename, options.filterRegex)) continue; // Apply regex filter if set

        try {
            auto fileSize = fs::file_size(entry.path());
            const std::string extension = entry.path().extension().string();
            fileStats[extension].count += 1;
            fileStats[extension].totalSize += fileSize;
        }
        catch (const fs::filesystem_error& e) {
            std::cerr << "Error reading file size: " << e.what() << '\n';
        }
    }
}

/*
* fn: scanDirectory
* brief: Scans the directory specified in the options,
* applying any set filters, and accumulates file statistics by extension.
* Handles directory traversal both recursively and non-recursively based on options.
* param: None - Uses the 'options' member variable for parameters.
* return: void .
*/
void FileData::scanDirectory() {
    fs::path dirPath(options.directory.empty() ? fs::current_path() : options.directory);

    if (!fs::exists(dirPath) || !fs::is_directory(dirPath)) {
        std::cerr << "Specified path is not a directory or does not exist: " << dirPath << std::endl;
        return;
    }

    // Use the appropriate iterator based on the recursive option
    if (options.recursive) {
        auto it = fs::recursive_directory_iterator(dirPath);
        for (const auto& entry : fs::recursive_directory_iterator(dirPath)) {
            if (!fs::is_regular_file(entry.status())) continue; // Skip if not a regular file

            std::string filename = entry.path().filename().string();
            // Apply regex filter if set
            if (options.isRegexSet && !std::regex_search(filename, options.filterRegex)) {
                //std::cout << "Skipping file not matching regex: " << filename << std::endl;
                continue; // Skip files not matching the regex pattern
            }

            try {
                auto fileSize = fs::file_size(entry.path());
                const std::string extension = entry.path().extension().string();
                fileStats[extension].count += 1;
                fileStats[extension].totalSize += fileSize;
            }
            catch (const fs::filesystem_error& e) {
                std::cerr << "Error reading file size: " << e.what() << '\n';
            }
        }
    }
    else {
        auto it = fs::directory_iterator(dirPath);
        for (const auto& entry : fs::recursive_directory_iterator(dirPath)) {
            if (!fs::is_regular_file(entry.status())) continue; // Skip if not a regular file

            std::string filename = entry.path().filename().string();
            // Apply regex filter if set
            if (options.isRegexSet && !std::regex_search(filename, options.filterRegex)) {
                std::cout << "Skipping file not matching regex: " << filename << std::endl;
                continue; // Skip files not matching the regex pattern
            }

            try {
                auto fileSize = fs::file_size(entry.path());
                const std::string extension = entry.path().extension().string();
                fileStats[extension].count += 1;
                fileStats[extension].totalSize += fileSize;
            }
            catch (const fs::filesystem_error& e) {
                std::cerr << "Error reading file size: " << e.what() << '\n';
            }
        }
    }
}
/*
* fn: accumulateFileStats
* brief: Adds or updates file statistics for a given filename by extracting its extension
* and updating the count and total size in the fileStats map.
* param: filename - The name of the file being processed.
*        fileSize - The size of the file being processed.
* return: void -  but updates the fileStats map directly.
*/
void FileData::accumulateFileStats(const std::string& filename, size_t fileSize) {
    const std::string extension = fs::path(filename).extension().string();

    fileStats[extension].count += 1;
    fileStats[extension].totalSize += fileSize;
}

/*
* fn: doesFileMatchFilter
* brief: Checks if the given filename matches the regex filter
* specified in the options.
* param: filename - The name of the file to check against the regex filter.
* return: bool - Returns true if the filename matches the filter regex, false otherwise.
*/

bool FileData::doesFileMatchFilter(const std::string& filename) const {
    return std::regex_search(filename, options.filterRegex);
}

/*
* fn: getFileStats
* brief: Getter for the file statistics map that has been populated by scanning directories and files.
* param: None - Operates on the internal fileStats map.
* return: const std::map<std::string,
* FileStats>& - Returns a constant reference to the map containing file statistics
* keyed by file extension.
*/

const std::map<std::string, FileStats>& FileData::getFileStats() const {
    return fileStats;
}