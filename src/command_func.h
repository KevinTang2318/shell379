#ifndef __COMMAND_FUNC__
#define __COMMAND_FUNC__

#include <sys/resource.h>
#include <vector>
#include <string>
#include <fcntl.h>
#include <signal.h>
#include <iostream>
#include "process_table.h"


void displayJobs(ProcessTable &pt, struct rusage &usage);

int runUserCommand(ProcessTable &pt, std::vector<std::string> commandArgs, std::string inputFile, std::string outputFile, bool isRunInBackground, std::string command);

void exitShell(ProcessTable &pt, struct rusage &usage);

int sendSignal(ProcessTable &pt, std::string pid, int sig);

int waitProcess(ProcessTable &pt, std::string pid);

#endif