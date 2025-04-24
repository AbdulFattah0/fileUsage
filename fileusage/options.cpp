#include "options.h"
#include <iostream>
#include <cstdlib> 

using namespace std;

Options::Options(int argc, char* argv[]) {
    parseArguments(argc, argv); 
}

/*
* fn: printHelp
* brief: Displays help information about the program's usage and command-line arguments.
* param: None
* return: void - Outputs help information to the standard output.
*/

void Options::printHelp() const {
    cout << "fileusage {v4.0.0} (c) 2024, Youssef Rajeh \n"
        << "  Usage: fileusage [--help] [-hrs(x regularexpression)] [folder]\n"
        << "  switches:\n"
        << "          h       help\n"
        << "          r       reverse the order of the listing\n"
        << "          s       sort by file sizes\n"
        << "          x       filter with a regular expression\n"
        << "  folder\n"
        << "          starting folder or current folder if not provided\n"; // Added newline for formatting
}

/*
* fn: parseArguments
* brief: Parses command-line arguments to configure program options such as help, sorting, and filtering.
* param: argc - The number of command-line arguments.
*        argv - An array of command-line arguments.
* return: void - Configures the Options object based on parsed arguments.
*/
void Options::parseArguments(int argc, char* argv[]) {
    directory = "."; 

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--help" || arg == "-h") {
            help = true;
        }
        else if (arg[0] == '-' && arg != "-") { 
            
            if (arg.length() > 1 && arg[1] != '-') {
                for (size_t j = 1; j < arg.length(); ++j) {
                    switch (arg[j]) {
                    case 'r':
                        reverse = true;
                        break;
                    case 's':
                        sortBySize = true;
                        break;
                    case 'x':
                        if (i + 1 < argc) {
                            filterRegex = std::regex(argv[++i], regex_constants::icase);
                            isRegexSet = true;
                            j = arg.length(); 
                        }
                        else {
                            cerr << "Option -x requires a regex pattern." << endl;
                            exit(EXIT_FAILURE);
                        }
                        break;
                    default:
                        cerr << "Unknown switch: " << arg[j] << endl;
                        exit(EXIT_FAILURE);
                    }
                }
            }
        }
        else {
            
            directory = arg;
            break; 
        }
    }
}