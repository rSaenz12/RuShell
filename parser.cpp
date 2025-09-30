//********************************************
// Author: Russell Saenz
// Program Name: Ru$hell
// FileName: parser.cpp
// Purpose: parsing user input
// Description: parses the user input strings, outputs a vector of tokens created from the string.
// Date: 09/28/2025
//********************************************

#include "parser.h"
#include <iostream>
#include <sstream>

using namespace std;

//beaking up user input into tokens
vector<string> parseInput(const string &userInput) {
    vector<string> tokens;
    //used in old parsing
    //istringstream iss(userInput);
    string token;
    bool inQuotes = false;

    //Changed the parsing because I wanted to include files that may have spaces in its name.
    // while (iss >> token) {
    //     tokens.push_back(token);
    // }

    //parsing that picks up spaces when files name is encapsulated by qoutations.
    //moving charecter by character allows for capture of whitespace if needed.
    for (size_t i = 0; i < userInput.size(); ++i) {
        char c = userInput[i];

        //first quote marks true, seconds closes
        if (c == '"') {
            inQuotes = !inQuotes;
            continue;
        }
        if (c == ' ' && !inQuotes) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        } else {
            token += c;
        }
    }

    //added so that user has to intentionally be using quotes
    if (inQuotes) {
        cerr << "ERROR: Unclosed Quotes" << endl;
        return {"*ERROR*"};
    }

    if (!token.empty()) {
        tokens.push_back(token);
    }

    return tokens;
}
