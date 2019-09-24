#include "headers.h"

void checkingCompletionOfBackgroundProcess() {
    for (int i = 0; i < noOfChildProcess; i++) {
        int stat;
        pid_t wpid;
        wpid = waitpid(childProcess[i], &stat, WNOHANG);
        if (wpid != 0) {
            printf("Process with pid = %d exited normally\n", childProcess[i]);
            noOfChildProcess--;
            i--;
            for (int j = i + 1; j < noOfChildProcess; j++)
                childProcess[j] = childProcess[j + 1];
        }
    }
}

void loop() {
    while (1) {
        signal(SIGCHLD, checkingCompletionOfBackgroundProcess);
        Display();
        char *str = malloc(sizeof(char) * 256);
        fgets(str, 256, stdin);
        int j = 0;
        char *newtoken = strtok(str, ";");
        while (newtoken != NULL) {
            commandArray[j++] = newtoken;
            newtoken = strtok(NULL, ";");
        }
        for (int x = 0; x < j; x++) {
            takeInput(x);
            if (processType == 0) {
                if ((strcmp(inputCommands[0], "cd") == 0) ||
                    (strcmp(inputCommands[0], "pwd") == 0) ||
                    (strcmp(inputCommands[0], "echo") == 0))
                    executeBuiltinCommand();
                else if ((strcmp(inputCommands[0], "ls") == 0))
                    executelsCommand();
                else if ((strcmp(inputCommands[0], "pinfo") == 0))
                    programinfo();
                else if ((strcmp(inputCommands[0], "history") == 0))
                    history();
                else if((strcmp(inputCommands[0], "nightswatch")==0))
                    nightswatch();
                else {
                    if (totalCommands >= 1) {
                        // last should point to NULL
                        inputCommands[totalCommands] = NULL;
                        pid_t pid, wait_pid;
                        int status;
                        pid = fork();
                        // error in forking
                        if (pid < 0) perror("error");
                        // child process
                        else if (pid == 0) {
                            if (execvp(inputCommands[0], inputCommands) == -1)
                                perror("error");
                            exit(EXIT_FAILURE);
                        } else {
                            wait_pid = waitpid(pid, &status, WUNTRACED);
                            while (!WIFEXITED(status) && !WIFSIGNALED(status))
                                wait_pid = waitpid(pid, &status, WUNTRACED);
                        }
                    }
                }
            } else if (processType == 1) {
                inputCommands[totalCommands - 1] = NULL;
                pid_t pid, wait_pid;
                pid = fork();
                // error in forking
                if (pid < 0) perror("error");
                // child process
                else if (pid == 0) {
                    if (execvp(inputCommands[0], inputCommands) == -1)
                        perror("error");
                    exit(EXIT_FAILURE);
                } else {
                    printf("Started process %d successfully\n", pid);
                    childProcess[noOfChildProcess] = pid;
                    noOfChildProcess += 1;
                }
            }
        }
    }
}

int main() {
    uname(&unameData);
    username = getlogin();
    char *directory = malloc(sizeof(char) * 256);
    getcwd(directory, 256);
    strcpy(homeDirectory, directory);
    free(directory);
    loop();
    return 0;
}