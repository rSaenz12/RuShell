//********************************************
// Author: Russell Saenz
// Program Name: Ru$hell
// FileName: commandExecuter.cpp
// Purpose: UNIX Shell command executer
// Description: Executes commands from vectors.
// Date: 09/28/2025
//********************************************

#include "commandExecuter.h"
#include "parser.h"
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <string>
#include <iostream>


using namespace std;


void commandExecution::executeCommand(std::vector<std::string> tokens) {
    //recieved if parser sends error
    if (tokens[0] == "*ERROR*") {
        return;
    }
    //help, hist, r n are internal commands
    if (tokens[0] == "help") {
        addCommandToHistory(tokens);

        cout << "\n";
        cout << "HELP" << endl;
        cout << "*WARNING ALL COMMANDS ARE CASE SENSITIVE*" << endl;
        cout << string(80, '-') << endl;
        cout << "cd JUMPBACK          jump to previous directory." << endl;
        cout << "cd 'target'          change directory to target directory." << endl;
        cout << "cd                   return to home directory." << endl;
        cout << "exit                 cause the shell to exit." << endl;
        cout << "hist                 display the (up to) 10 most recent commands entered." << endl;
        cout << "progname [args]      run the program progname with the given, possibly optional, arguments." << endl;
        cout << "path t/f             show current directory path, true to show, false to hide." << endl;
        cout << "r n                  execute the nth command from the history list." << endl;
        cout << string(80, '-') << endl;
        cout << "\n";

        return;
    }
    if (tokens[0] == "hist") {
        addCommandToHistory(tokens);
        displayCommandHistory();

        return;
    }
    if (tokens[0] == "r") {
        if (tokens.size() < 2) {
            runNthCommand("mostRecent");

            return;
        }
        runNthCommand(tokens[1]);

        return;
    }
    if (tokens[0] == "path") {
        if (tokens[1] == "true") {
            showDirectory = true;
        } else if (tokens[1] == "false") {
            showDirectory = false;
        }
        return;
    }
    // execvp doesnt handle cd directly
    if (tokens[0] == "cd") {
        addCommandToHistory(tokens);

        //cd alone goes to the home directory (token.size()==1)
        if (tokens.size() < 2) {
            //if using cd to elevate, and the stack is not empty, will elevate and pop stack.
            if (chdir(homeDirectory.c_str()) != 0) {
                perror("cd");
            } else {
                pastDirectory.push(currentDirectory);
                currentDirectory = get_current_dir_name();
            }
        } else if (tokens[1] == "JUMPBACK") {
            //if using cd JUMPBACK to elevate, and the stack is not empty, will elevate and pop stack.
            if (!pastDirectory.empty()) {
                if (chdir(pastDirectory.top().c_str()) != 0) {
                    perror("cd");
                } else {
                    pastDirectory.pop();
                    currentDirectory = get_current_dir_name();
                }
            } else {
                //else (the stack is empty), stays in the same directory.
                return;
            }
        } else {
            //changes directory to the targeted one.
            if (chdir(tokens[1].c_str()) != 0) {
                perror("cd");
            } else {
                pastDirectory.push(currentDirectory);
                currentDirectory = get_current_dir_name();
            }
        }
        return;
    }

    //handle progname commands with execvp

    addCommandToHistory(tokens);

    pid_t processId = fork();

    //problem when creating child process
    if (processId < 0) {
        perror("fork");

        return;
    }

    //child process
    if (processId == 0) {
        vector<char *> command;

        //have to convert to c strings for execvp
        for (auto &token: tokens) {
            command.push_back(&token[0]);
        }
        //null ends argument
        command.push_back(nullptr);
        execvp(command[0], command.data());
        //execvp failed
        perror("execvp");
        //exits child process
        exit(EXIT_FAILURE);
    }

    //waiting for child process to finish
    int status;
    waitpid(processId, &status, 0);
}

void commandExecution::addCommandToHistory(const vector<string> &tokens) {
    string command;

    for (const auto &token: tokens) {
        command += " " + token;
    }

    //max of the previous commands kept set to 10
    if (previousCommands.size() >= 10) {
        previousCommands.pop_back();
        previousCommands.push_back(command);

        return;
    }
    previousCommands.push_back(command);
}

//lower the number, more recent the command was
//for opposite effect, use i+1 instead of size-i
void commandExecution::displayCommandHistory() {
    for (int i = 0; i < previousCommands.size(); i++) {
        std::cout << previousCommands.size() - i << ". " << previousCommands[i] << std::endl;
    }
    cout << "\n";
}

void commandExecution::runNthCommand(const string &nthCommand) {
    //base case for most recent command when using just r.
    if (nthCommand == "mostRecent") {
        int mostRecentIndex = previousCommands.size() - 1;

        cout << "RuShell>" << previousCommands[mostRecentIndex] << endl;
        vector<string> mostRecentCommand = parseInput(previousCommands[mostRecentIndex]);

        executeCommand(mostRecentCommand);

        return;
    }

    int nthCommandNumber = stoi(nthCommand);

    //check validity (1-10)
    if (nthCommandNumber > previousCommands.size() || nthCommandNumber < 1) {
        cout << "command " << nthCommand << " out of bounds" << endl;

        return;
    }

    // use nthCommandNumber-1 instead of size - nthCommandNumber if reversing order on displayCommandHistory;
    int index = previousCommands.size() - nthCommandNumber;
    cout << "RuShell>" << previousCommands[index] << endl;
    vector<string> command = parseInput(previousCommands[index]);

    executeCommand(command);
}

string commandExecution::returnCurrentDirectory() {
    return currentDirectory;
}

bool commandExecution::returnShowDirectoryStatus() {
    return showDirectory;
}
