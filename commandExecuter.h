//********************************************
// Author: Russell Saenz
// Program Name: Ru$hell
// FileName: commandExecuter.h
// Purpose: Class file for commandExecuter.cpp
// Date: 09/28/2025
//********************************************

#ifndef SHELLPROGRAM_COMMANDEXECUTER_H
#define SHELLPROGRAM_COMMANDEXECUTER_H

#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <stack>

class commandExecution {
private:
    std::vector<std::string> previousCommands;
    std::stack<std::string> pastDirectory;
    std::string homeDirectory = std::getenv("HOME");
    std::string currentDirectory = homeDirectory;
    bool showDirectory = false;

public:
    void executeCommand(std::vector<std::string> tokens);

    void addCommandToHistory(const std::vector<std::string>& tokens);

    void displayCommandHistory();

    void runNthCommand(const std::string& nthCommand);

    std::string returnCurrentDirectory();
    bool returnShowDirectoryStatus();
    
};


#endif //SHELLPROGRAM_COMMANDEXECUTER_H
