#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Invalid sleeper usage! Slepper requires exactly 1 argument.\n");
        return -1;
    }

    int seconds = atoi(argv[1]);
    sleep(seconds);
    printf("Sleep done.\n");

    return 0;
}