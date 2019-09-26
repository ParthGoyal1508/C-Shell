#include "headers.h"

void checkingCompletionOfBackgroundProcess()
{
    for (int i = 0; i < noOfChildProcess; i++)
    {
        int stat;
        pid_t wpid;
        wpid = waitpid(childProcess[i], &stat, WNOHANG);
        if (wpid != 0)
        {
            printf("Process with pid = %d exited normally\n", childProcess[i]);
            noOfChildProcess--;
            i--;
            for (int j = i + 1; j < noOfChildProcess; j++)
                childProcess[j] = childProcess[j + 1];
            Display();
            fflush(stdout);
        }
    }
    return;
}

void loop()
{
    while (1)
    {
        signal(SIGCHLD, checkingCompletionOfBackgroundProcess);
        Display();
        char *str = malloc(sizeof(char) * 256);
        fgets(str, 256, stdin);
        int j = 0;
        char *newtoken = strtok(str, ";");
        while (newtoken != NULL)
        {
            commandArray[j++] = newtoken;
            newtoken = strtok(NULL, ";");
        }
        for (int x = 0; x < j; x++)
        {
            takeInput(x);
            //foreground process
            if (processType == 0)
            {
                if (redirection == 0)
                {
                    if ((strcmp(inputCommands[0], "cd") == 0) ||
                        (strcmp(inputCommands[0], "pwd") == 0) ||
                        strcmp(inputCommands[0], "echo") == 0)
                        executeBuiltinCommand();
                    else if ((strcmp(inputCommands[0], "ls") == 0))
                        executelsCommand();
                    else if ((strcmp(inputCommands[0], "pinfo") == 0))
                        programinfo();
                    else if ((strcmp(inputCommands[0], "history") == 0))
                        history();
                    else if ((strcmp(inputCommands[0], "nightswatch") == 0))
                        nightswatch();
                    else if ((strcmp(inputCommands[0], "setenv") == 0))
                        set_env();
                    else if ((strcmp(inputCommands[0], "unsetenv") == 0))
                        unset_env();
                }
                else
                {
                    if (totalCommands >= 1)
                    {
                        // last should point to NULL
                        inputCommands[totalCommands] = NULL;
                        pid_t pid, wait_pid;
                        int status;
                        pid = fork();
                        // error in forking
                        if (pid < 0)
                            perror("error");
                        // child process
                        else if (pid == 0)
                        {
                            int point_stdout = dup(1), point_stdin = dup(0);
                            for (int i = 0; i < totalCommands; i++)
                            {
                                if (strcmp(inputCommands[i], "<") == 0)
                                {
                                    inputCommands[i] = NULL;
                                    int fd = open(inputCommands[i + 1], O_RDONLY, 0);
                                    if (fd < 0)
                                        perror("Error opening input file");
                                    if (dup2(fd, 0) < 0)
                                        perror("Error in duplication");
                                    close(fd);
                                }
                                else if (strcmp(inputCommands[i], ">") == 0)
                                {
                                    inputCommands[i] = NULL;
                                    struct stat st;
                                    int fd;
                                    if (stat(inputCommands[i + 1], &st) == 0)
                                        fd = open(inputCommands[i + 1], O_WRONLY | O_TRUNC, 0644);
                                    else
                                        fd = open(inputCommands[i + 1], O_CREAT | O_WRONLY, 0644);
                                    if (fd < 0)
                                        perror("Error in redirection");
                                    if (dup2(fd, 1) < 0)
                                        perror("Error in duplication");
                                    close(fd);
                                }
                                else if (strcmp(inputCommands[i], ">>") == 0)
                                {
                                    inputCommands[i] = NULL;
                                    struct stat st;
                                    int fd;
                                    if (stat(inputCommands[i + 1], &st) == 0)
                                    {
                                        fd = open(inputCommands[i + 1], O_WRONLY | O_APPEND, 0644);
                                    }
                                    else
                                    {
                                        fd = open(inputCommands[i + 1], O_CREAT | O_WRONLY, 0644);
                                    }
                                    if (fd < 0)
                                        perror("Error in appending");
                                    if (dup2(fd, 1) < 0)
                                        perror("Error in duplication");
                                    close(fd);
                                }
                            }
                            if (execvp(inputCommands[0], inputCommands) == -1)
                                perror("error");
                            dup2(point_stdin, 0);
                            dup2(point_stdout, 1);
                            exit(EXIT_FAILURE);
                        }
                        else
                        {
                            wait_pid = waitpid(pid, &status, WUNTRACED);
                            while (!WIFEXITED(status) && !WIFSIGNALED(status))
                                wait_pid = waitpid(pid, &status, WUNTRACED);
                        }
                    }
                }
            }
            //background process
            else if (processType == 1)
            {
                inputCommands[totalCommands - 1] = NULL;
                pid_t pid, wait_pid;
                pid = fork();
                // error in forking
                if (pid < 0)
                    perror("error");
                // child process
                else if (pid == 0)
                {
                    if (execvp(inputCommands[0], inputCommands) == -1)
                        perror("error");
                    exit(EXIT_FAILURE);
                }
                else
                {
                    printf("Started process %d successfully\n", pid);
                    childProcess[noOfChildProcess] = pid;
                    noOfChildProcess += 1;
                }
            }
        }
    }
}

int main()
{
    uname(&unameData);
    username = getlogin();
    char *directory = malloc(sizeof(char) * 256);
    getcwd(directory, 256);
    strcpy(homeDirectory, directory);
    free(directory);
    loop();
    return 0;
}