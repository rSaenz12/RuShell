//********************************************
// Author: Russell Saenz
// Program Name: Ru$hell
// FileName: main.cpp
// Purpose: UNIX Shell main driver file
// Description: UNIX Shell that accepts users inputs, parses them then runs commands.
// Date: 09/28/2025
//********************************************

#include <iostream>
#include "parser.h"
#include "commandExecuter.h"

using namespace std;

int main() {
    //setting starting directory to home.
    if (chdir(std::getenv("HOME")) != 0) {
        perror("cd");
        return 0;
    }


    string userInput;
    cout << "Welcome to Ru$hell" << endl;
    cout << "*ENTER 'help' FOR HELP*" << endl;
    cout << "\n" << endl;

    commandExecution command;

    while (true) {
        if (!command.returnCurrentDirectory().empty() && command.returnShowDirectoryStatus()) {
            cout << "[Ru$hell]" << command.returnCurrentDirectory() << ">> ";
        } else { cout << "Ru$hell>> "; }

        //getLine used so that full line is grabbed
        getline(cin, userInput);
        cout << "\n";

        if (userInput == "exit") {
            cout << "Exited Successfully" << endl;
            return 0;
        }

        //fills vector with parsed input, tokens broken up at white spaces
        auto tokens = parseInput(userInput);

        command.executeCommand(tokens);
    }
}
