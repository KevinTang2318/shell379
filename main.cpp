/*
    This code controls the overall process of shell379 and handles the exit input
*/

#include "shell_runner.h"
#include <iostream>

int main(void) {
    std::string input;
    bool exitStatus = false;
    ShellRunner shellRunner;  // a shell object used to execute functions and store commands

    while (!exitStatus) {
        // Read user input
        printf("SHELL379: ");
        std::getline(std::cin, input);

        if (shellRunner.parseCmd(input) < 0) { // a return value less than 0 means the given command is invalid
            shellRunner.clean();
            continue;
        } 
        
        shellRunner.executeCmd();
        shellRunner.clean();
    }

    return 0;
}