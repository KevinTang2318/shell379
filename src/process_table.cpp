#include "process_table.h"

using namespace std;

// Parse command-line outputs, separate each element
vector<string> getInformation(string input) {
    vector<string> args;
    istringstream inputStream(input);
    string temp;

    while (inputStream >> temp) {
        args.push_back(temp);
    }

    return args;
}

// Calculate the time taken based on the given string
int calculateTime(string timeStr) {
    int hour = stoi(timeStr.substr(0, 2));
    int minutes = stoi(timeStr.substr(3, 2));
    int seconds = stoi(timeStr.substr(6,2));

    return hour * 3600 + minutes * 60 + seconds;
}

//--------------------------------- Class Member Functions ---------------------------------------------

// Get the current status of processes using ps command, and update process_table accordingly
void ProcessTable::update() {
    FILE *fp;
    char buf[150];
    vector<string> psOutput;

    fp = popen("ps -o pid,state,time,command", "r");  //use ps command to get the current status of processes 

    if (fp == NULL)
        perror("Failed executing ps command!");


    // First set the existance of all processes to false, will change later if the process is in the table
    for (int i = 0; i < processes.size(); i++) {
        processes[i].setStatusInPt(false);
    }

    // process information line by line
    while (fgets(buf, 150, fp) != NULL) {
        psOutput = getInformation((string) buf);
        
        for (int i = 0; i < processes.size(); i++) {
            char pid[20];
            sprintf(pid, "%d", processes[i].getPid());  // get pid from current process entry

            // Situation when current process is in process table
            if (strcmp(pid, psOutput[0].c_str()) == 0) {
                processes[i].setStatus(psOutput[1]);
                processes[i].setStatusInPt(true);
                processes[i].setTime(calculateTime(psOutput[2]));
            }
        }
    }

    // Remove the processes that has already finished
    for (int i = 0; i < processes.size(); i++) {
        if (!processes[i].getStatusInPt()) {
            processes.erase(processes.begin() + i);  //! Here might have some errors
        }
    }

    pclose(fp);
}

// Get the current size of the process table
int ProcessTable::size() {
    return processes.size();
}

// Add an entry to the process table
void ProcessTable::add(Process process) {
    processes.push_back(process);
}

// Return the element at the given index in the table
Process ProcessTable::at(int index) {
    return this->processes[index];
}