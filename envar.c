#include "headers.h"

void set_env()
{
    if (totalCommands == 1)
        printf("Arguments expected: {1,2} , given: 0\n");
    else if (totalCommands > 3)
        printf("Too many arguments\n");
    else
    {
        if (totalCommands == 3){
            setenv(inputCommands[1], inputCommands[2], 2);
            printf("variable set\n");
        }
        else if (totalCommands == 2)
            setenv(inputCommands[1], " ", 2);
    }
    return;
}

void unset_env()
{
    if (totalCommands == 1 || totalCommands > 2)
        printf("ERROR , exactly 1 argument required");
    else
        unsetenv(inputCommands[1]);
    return;
}