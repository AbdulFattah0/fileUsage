#include "options.h"
#include "fileData.h" // Make sure to include the header for FileData
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    Options options;

    try {
        options.parseArguments(argc, argv);
    }
    catch (const exception& e) {
        cerr << "Error parsing arguments: " << e.what() << endl;
        return 1;
    }

    if (options.shouldShowHelp()) {
        options.printHelp();
        return 0;
    }

    // Check if the -x switch was used and obtain the regex pattern if so
    if (options.shouldUseRegex()) {
        // Perform directory traversal with regex filtering
        FileData::traverseDirectory(options.getFolderPath(), options.getRegexPattern(), true);
    }
    else {
        // Perform directory traversal without regex filtering
        FileData::traverseDirectory(options.getFolderPath());
    }

    return 0;
}
