#include "headers.h"

void executeBuiltinCommand() {
    // cd command
    if (strcmp(inputCommands[0], "cd") == 0) {
        if (totalCommands == 1) {
            chdir(homeDirectory);
        } else {
            if (inputCommands[1][0] == '~') {
                char finalPath[256] = "";
                strcat(finalPath, homeDirectory);
                for (int i = strlen(homeDirectory);
                     i <= strlen(homeDirectory) + strlen(inputCommands[1]) - 1;
                     i++) {
                    finalPath[i] =
                        inputCommands[1][i - strlen(homeDirectory) + 1];
                }
                chdir(finalPath);
            } else if (chdir(inputCommands[1]) == -1) {
                printf("Directory does not exist\n");
            }
        }
        return;
    }
    // pwd command
    if (strcmp(inputCommands[0], "pwd") == 0) {
        char presentDirectory[256];
        getcwd(presentDirectory, 256);
        printf("%s\n", presentDirectory);
        return;
    }
    // echo command
    if (strcmp(inputCommands[0], "echo") == 0) {
        for (int i = 1; i < totalCommands; i++) printf("%s ", inputCommands[i]);
        printf("\n");
        return;
    }
    return;
}
