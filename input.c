#include "headers.h"

void storeCommandInHistory() {
    char *command = malloc(sizeof(char) * 256);
    strcpy(command, inputCommands[0]);
    for (int i = 1; i < totalCommands; i++) {
        strcat(command, " ");
        strcat(command, inputCommands[i]);
    }
    if (noOfhistoryCommands <= 19) {
        if (noOfhistoryCommands == 0)
            historyArray[noOfhistoryCommands++] = command;
        else if (strcmp(historyArray[noOfhistoryCommands-1], command) != 0)
            historyArray[noOfhistoryCommands++] = command;
    } else {
        for (int i = 0; i < 19; i++) {
            historyArray[i] = historyArray[i + 1];
        }
        if (strcmp(historyArray[noOfhistoryCommands], command) != 0)
            historyArray[19] = command;
    }
}

void clearInputCommands() {
    for (int i = 0; i < 256; i++) inputCommands[i] = NULL;
    totalCommands = 0;
}
void takeInput(int x) {
    // take input
    processType = -1;
    redirection = 0;

    char *str = malloc(sizeof(char) * 256);
    strcpy(str, commandArray[x]);
    char *token;
    char *delimiter = " \t\n";
    clearInputCommands();
    int i = 0;
    token = strtok(str, delimiter);

    while (token != NULL) {
        inputCommands[i++] = token;
        token = strtok(NULL, delimiter);
    }

    totalCommands = i;
    if (totalCommands >= 1) {
        if (strcmp(inputCommands[totalCommands - 1], "&") == 0)
            processType = 1;
        else
            processType = 0;
    }

    for(int i=0;i<totalCommands;i++){
        if((strcmp(inputCommands[i],"<")==0) || (strcmp(inputCommands[i],">")==0) || (strcmp(inputCommands[i],">>")==0))
            redirection = 1;
    }

    if (totalCommands > 0) storeCommandInHistory();

    return;
}
