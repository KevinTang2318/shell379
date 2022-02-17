#include "shell_runner.h"

using namespace std;

ShellRunner::ShellRunner() {
    // Initialize all attributes
    args.clear();
    inputFile.clear();
    outputFile.clear();
    commandLine.clear();
    isRunInBackground = false;
}

// Process the given input, extract command and execute the corresponding function
int ShellRunner::parseCmd(std::string input) {
    int argCount = 0;
    string arg;
    istringstream inputStream(input);

    // Check if the input is too long
    if (input.length() > LINE_LENGTH || input.length() == 0) {
        printf("Command length invalid, please enter a non-empty command within 100 characters.\n");
        return -1;
    }

    commandLine = input; // Record the current command

    while (inputStream >> arg) {
        // Check whether each argument is too long
        if (arg.length() > MAX_LENGTH) {
            printf("Argument too long!\n");
            return -1;
        }

        argCount++;

        // Check whether each argument is valid
        if (argCount > MAX_ARGS) {
            printf("Too many arguments in the command, please enter a command with less than 7 arguments.\n");
            return -1;
        }

        // Check whether the command requires to run in background
        if (arg == "&") {
            if (!isRunInBackground) {  //check whether there's only 1 & entry
                isRunInBackground = true;
                args.push_back(arg); // we temporarily push this element in the arg vector to check whether it's the last argument. If not, we don't process this command.
                continue;
            }
            else {
                printf("Invalid command! The command can contain only 1 & entry!\n");
                return -1;
            }
        }

        // check whether the command gives custom input or output files
        if (arg.find("<") == 0) {
            inputFile = arg.substr(1);
            continue;
        }

        if (arg.find(">") == 0) {
            outputFile = arg.substr(1);
            continue;
        }

        args.push_back(arg); // add argument to argument list
    }

    // When the & is not at the end of a command, we consider this as invalid
    if (isRunInBackground && args.back() != "&") { 
        printf("Invalid command! The & sign has to be at the end of the command!\n");
        return -1;
    }
    else {
        if (isRunInBackground)
            args.pop_back();
    }
    return 0;
}

void ShellRunner::executeCmd() {
    int ret;
    // Execute the corresponding command
    if (strcmp(args[0].c_str(), "exit") == 0)
    {
        exitShell(pt, usage);
    }
    else if (strcmp(args[0].c_str(), "jobs") == 0) {
        displayJobs(pt, usage);
    }
    else if (strcmp(args[0].c_str(), "kill") == 0) {
        ret = sendSignal(pt, args[1], SIGKILL);
        if (ret < 0)
            printf("Killing process %s failed!\n", args[1].c_str());
    }
    else if (strcmp(args[0].c_str(), "resume") == 0) {
        ret = sendSignal(pt, args[1], SIGCONT);
        if (ret < 0)
            printf("Resuming process %s failed!\n", args[1].c_str());
    }
    else if (strcmp(args[0].c_str(), "sleep") == 0) {
        ret = runUserCommand(pt, args, inputFile, outputFile, isRunInBackground, commandLine);
        if (ret < 0)
            printf("Sleep failed!\n");
    }
    else if (strcmp(args[0].c_str(), "suspend") == 0) {
        ret = sendSignal(pt, args[1], SIGSTOP);
        if (ret < 0)
            printf("Stopping process %s failed!\n", args[1].c_str());
    }
    else if (strcmp(args[0].c_str(), "wait") == 0) {
        ret = waitProcess(pt, args[1]);
        if (ret < 0)
            printf("Wait process %s failed!\n", args[1].c_str());
    }
    else {
        ret = runUserCommand(pt, args, inputFile, outputFile, isRunInBackground, commandLine);
        if (ret < 0)
            printf("Run user command failed!\n");
    }

    //TODO: Finish all actual methods
}

void ShellRunner::clean() {
    // Clean the previous entry
    args.clear();
    inputFile.clear();
    outputFile.clear();
    commandLine.clear();
    isRunInBackground = false;
}