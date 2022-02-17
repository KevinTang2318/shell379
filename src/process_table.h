#ifndef __PROCESS_TABLE__
#define __PROCESS_TABLE__

#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
#include <sstream>
#include <iostream>
#include "process.h"

class ProcessTable {
    private:
        std::vector<Process> processes;
    
    public:
        void update();
        int size();
        void add(Process process);

        Process at(int index);
};

#endif