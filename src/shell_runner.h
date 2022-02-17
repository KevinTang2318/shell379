/*
    This code defines the functional methods for shell 379
*/

#ifndef __SHELL_RUNNER__
#define __SHELL_RUNNER__

#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include "command_func.h"

#define LINE_LENGTH    100  // Max # of characters in an input line
#define MAX_ARGS         7  // Max number of arguments to a command
#define MAX_LENGTH      20  // Max # of characters in an argument
#define MAX_PT_ENTRIES  32  // Max entries in the Process Table


class ShellRunner {

    //Class attributes
    public:
        ProcessTable pt;
        struct rusage usage;

    private:
        std::string commandLine;
        std::vector<std::string> args;
        std::string inputFile;
        std::string outputFile;
        bool isRunInBackground = false;


    public:
        ShellRunner();

        int parseCmd(std::string input);
        void executeCmd();
        void clean();
};

#endif