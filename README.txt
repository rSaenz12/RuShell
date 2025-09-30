Author: Russell Saenz
contact: rsaenz12@islander.tamucc.edu

Description:
The program Ru$hell is a UNIX shell that supports the following internal commands:
cd JUMPBACK: return to the previous directory
cd 'target': change directory to the specified target
cd:  return to home directory.
hist: display the last 10 commands
help: display help information
exit: exit the shell
path t/f: show or hide the current directory path
r n: execute the nth command from history

External UNIX commands are executed through execvp().

References:
- execvp(): https://www.digitalocean.com/community/tutorials/execvp-function-c-plus-plus
- chdir(): https://www.geeksforgeeks.org/linux-unix/chdir-in-c-language-with-examples/
- fork(): https://www.geeksforgeeks.org/c/fork-system-call/

Files in Directory:
- main.cpp
- commandExecuter.cpp
- commandExecuter.h
- parser.cpp
- parser.h
- Makefile

Instructions:
1. Make a directory
2. Insert main.cpp, commandExecuter.cpp, commandExecuter.h, parser.cpp, parser.h, Makefile

Execution:
1. Run `make` in the directory to compile the program.
2. Run `./RuShell` to start the shell.
3. Run `make clean` to remove object files (.o).
4. Run `make distclean` to remove the compiled program.

