#include "headers.h"

void Display() {
    char presentDirectory[256] = "";
    getcwd(presentDirectory, 256);
    char relativeDirectory[256] = "";
    int i = 0;
    for (i = 0; i < strlen(homeDirectory); i++) {
        if (homeDirectory[i] == presentDirectory[i])
            continue;
        else
            break;
    }
    if (i == strlen(homeDirectory)) {
        relativeDirectory[0] = '~';
        while (presentDirectory[i] != '\0') {
            relativeDirectory[i - strlen(homeDirectory) + 1] =
                presentDirectory[i];
            i++;
        }
    } else {
        for (int i = 0; i < strlen(presentDirectory); i++)
            relativeDirectory[i] = presentDirectory[i];
    }
    printf("<%s@%s:%s>", username, unameData.nodename, relativeDirectory);
}
