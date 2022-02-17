#include "command_func.h"

using namespace std;

// Signal Handler for forked child processes
void childSignalHandler(int code) {
    wait(NULL);
}

// Displays detailed information about the current processes
void displayJobs(ProcessTable &pt, struct rusage &usage) {
    pt.update();

    int rProcessCount = pt.size();
    getrusage(RUSAGE_CHILDREN, &usage);

    // Display formatted information
    printf("\n");
    printf("Running processes: \n");

    if (rProcessCount > 0) {
        printf(" #%8s %1s %3s %-10s\n", "PID", "S", "SEC", "COMMAND");
        for (int i = 0; i < pt.size(); i++) {
            printf(" %1d: %6d %1s %3d %-10s\n", i, pt.at(i).getPid(), pt.at(i).getStatus().c_str(), pt.at(i).getTime(), pt.at(i).getCmd().c_str());
        }
    }

    printf("Processes = %6d active\n", rProcessCount);
    printf("Completed processes: \n");
    printf("User time = %6d seconds\n", usage.ru_utime.tv_sec);
    printf("Sys  time = %6d seconds\n", usage.ru_stime.tv_sec);
    printf("\n");
}

// This function takes a non-shell379 command, execute it and add it to the process table
int runUserCommand(ProcessTable &pt, std::vector<std::string> commandArgs, std::string inputFile, std::string outputFile, bool isRunInBackground, string command) {
    pid_t childPid = fork();
    if (childPid < 0) {
        perror("Create child process failed!");
        return -1;
    }
    else if (childPid == 0) {
        // Here are the operations to complete in the child process

        //check if the instruction is "sleep"
        if (strcmp(commandArgs[0].c_str(), "sleep") == 0) {
            sleep(stoi(commandArgs[1]));
        }
        else {
            // First process input & output redirection if needed
            if (!inputFile.empty()) {
                int fd = open(inputFile.c_str(), O_RDONLY);
                if (fd < 0) {
                    perror("Open input source file failed!");
                    return -1;
                }
                dup2(fd, STDIN_FILENO);  // connect file to stdin
                close(fd);
            }

            if (!outputFile.empty()) {
                int fd = open(outputFile.c_str(), O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
                if (fd < 0) {
                    perror("Open output source file failed!");
                    return -1;
                }
                dup2(fd, STDOUT_FILENO); // connect file with stdout
                close(fd);
            }

            // Form char* array with the parsed inputs
            vector<char*> args(commandArgs.size() + 1);
            for (int i = 0; i < commandArgs.size(); i++) {
                args[i] = &commandArgs[i][0];
            }   

            // Execute command
            if (execvp(args[0], args.data()) < 0)
                perror("Failed to exec the program");
        }
    }
    else {
        // code for main process
        if (!isRunInBackground) {
            // If not run in background, wait until process finishes
            signal(SIGCHLD, SIG_DFL);
            int status;
            waitpid(childPid, &status, WUNTRACED);
        }
        else {
            // If run in background, add the process to the process table 
            signal(SIGCHLD, childSignalHandler);
            Process newProcess = Process(childPid, command);
            pt.add(newProcess);
        }
    }
    return 0;
}

// Function that exits the entire program
void exitShell(ProcessTable &pt, struct rusage &usage) {
    pt.update(); // Before exiting, update the process table to get all currently running processes

    // Kill all processes
    for (int i = 0; i < pt.size(); i++) {
        if (kill(pt.at(i).getPid(), SIGKILL) != 0) {
            perror("Cannot terminate all processes, please try again!");
            return;
        }
    }

    // Wait for processes to terminate
    while (wait(NULL) > 0);

    // Get final time
    getrusage(RUSAGE_CHILDREN, &usage);
    
    // print formatted information
    printf("\n");
    printf("Resource used\n");
    printf("User time = %6d seconds\n", usage.ru_utime.tv_sec);
    printf("Sys  time = %6d seconds\n", usage.ru_stime.tv_sec);
    printf("\n");
    
    _exit(EXIT_SUCCESS);
}

// Function that sends the given signal to the given process
int sendSignal(ProcessTable &pt, std::string pid, int sig) {
    pt.update(); // update the process table to get all currently running processes

    // Find the corresponding process in the process table
    // if the process doesn't exist, return an error
    for (int i = 0; i < pt.size(); i++)
    {
        if (stoi(pid) == pt.at(i).getPid()) {
            if (kill(stoi(pid), sig) == 0) {
                return 0;
            }
        }
    }

    perror("Failed send signal to the given process!");
    return -1;
}

// wait for the given process to finish
int waitProcess(ProcessTable &pt, std::string pid) {
    pt.update(); // update the process table to get all currently running processes
    int state;

    // Find the corresponding process in the process table
    // if the process doesn't exist, return an error
    for (int i = 0; i < pt.size(); i++)
    {
        if (stoi(pid) == pt.at(i).getPid()) {
            waitpid(stoi(pid), &state, WUNTRACED);
            return 0;
        }
    }

    perror("The indicated process does not exist!");
    return -1;
}