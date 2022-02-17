#include "process.h"

using namespace std;

Process::Process(pid_t pid, string command) {
    this->pid = pid;
    this->cmd = command;
}

// Getters and setters
pid_t Process::getPid() {
    return this->pid;
}

string Process::getStatus() {
    return this->status;
}

int Process::getTime() {
    return this->time;
}

string Process::getCmd() {
    return this->cmd;
}

bool Process::getStatusInPt() {
    return this->isInPt;
}

void Process::setStatus(string status) {
    this->status = status;
}

void Process::setStatusInPt(bool status) {
    this->isInPt = status;
}
void Process::setTime(int time) {
    this->time = time;
}