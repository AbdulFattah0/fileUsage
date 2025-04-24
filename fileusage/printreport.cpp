#include "printreport.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <set>

using namespace std;

// Constructor: Accepts the file statistics map and the options used for generating the report
PrintReport::PrintReport(const map<string, FileStats>& fileStats, const Options& options)
    : fileStats(fileStats), options(options) {}

/*
* fn: execute()
* brief: Generates and prints a detailed report of file statistics,
* including the count and total size of files grouped by their extensions.
* The report can be sorted by file size or extension, in ascending or descending order,
* based on user-selected options.
*
* param: None
*
* return: void()
*
*/
void PrintReport::execute() {
    // Convert map to a vector for sorting
    vector<pair<string, FileStats>> items(fileStats.begin(), fileStats.end());

    // Sorting logic
    if (options.sortBySize) {
        if (options.reverse) {
            sort(items.begin(), items.end(), [](const auto& a, const auto& b) {
                return a.second.totalSize != b.second.totalSize ? a.second.totalSize > b.second.totalSize : a.first > b.first;
                });
        }
        else {
            sort(items.begin(), items.end(), [](const auto& a, const auto& b) {
                return a.second.totalSize != b.second.totalSize ? a.second.totalSize < b.second.totalSize : a.first < b.first;
                });
        }
    }
    else { // Default to sorting by extension
        if (options.reverse) {
            sort(items.begin(), items.end(), [](const auto& a, const auto& b) {
                return a.first > b.first;
                });
        }
        else {
            sort(items.begin(), items.end(), [](const auto& a, const auto& b) {
                return a.first < b.first;
                });
        }
    }

    
    cout << left << setw(22) << "Ext" << right << setw(5) << "#" << setw(20) << "Total" << endl << endl;

    
    size_t totalFiles = 0;
    size_t totalSize = 0;

    
    locale locale("");
    cout.imbue(locale);

    
    for (const auto& [extension, stats] : items) {
        cout << left << setw(22) << extension << right << setw(5) << stats.count << setw(20) << fixed << stats.totalSize << endl;
        totalFiles += stats.count;
        totalSize += stats.totalSize;
    }

    
    cout << endl;
    cout << left << setw(25) << items.size() << setw(15) << totalFiles << setw(5) << totalSize << endl;
};
