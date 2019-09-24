#include "headers.h"

void history() {
    if (totalCommands == 2) {
        if (atoi(inputCommands[1]) > 10) {
            printf("Maximum no of command can show is 10\n");
            int i = noOfhistoryCommands - 10;
            if (i < 0) i = 0;
            for (int j = i; j < noOfhistoryCommands; j++) {
                printf("%s\n", historyArray[j]);
            }
        } else {
            int i = noOfhistoryCommands - atoi(inputCommands[1]);
            if (i < 0) i = 0;
            for (int j = i; j < noOfhistoryCommands; j++) {
                printf("%s\n", historyArray[j]);
            }
        }
    } else {
        if (noOfhistoryCommands > 10) {
            for (int j = noOfhistoryCommands-10; j < noOfhistoryCommands; j++) {
                printf("%s\n", historyArray[j]);
            }

        } else {
            for (int j = 0; j < noOfhistoryCommands; j++) {
                printf("%s\n", historyArray[j]);
            }
        }
    }
    return;
}