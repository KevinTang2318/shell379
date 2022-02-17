/* 
    The Process class contains all attributes for a process
*/

#ifndef __PROCESS__
#define __PROCESS__

#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

class Process {
    private:
        pid_t pid;
        std::string status; // 1 for running, 0 for suspended and -1 for stopped
        int time;  // stores the time a process has taken to run
        bool isInPt = false;
        std::string cmd;

    public:
        Process(pid_t pid, std::string command);
        pid_t getPid();
        std::string getStatus();
        int getTime();
        std::string getCmd();
        bool getStatusInPt();

        void setStatus(std::string status);
        void setStatusInPt(bool status);
        void setTime(int time);

};

#endif