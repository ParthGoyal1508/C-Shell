#include "headers.h"

void programinfo() {
    int pid;
    if (inputCommands[1] == NULL) {
        pid = getpid();
    } else {
        pid = atoi(inputCommands[1]);  // convert pid into integer from string
        if (kill(pid, 0) == -1) {
            printf("Invalid pid\n");
            return;
        }
    }

    char* stats = (char*)malloc(256 * sizeof(char));
    sprintf(stats, "/proc/%d/stat", pid);
    FILE* stat = fopen(stats, "r");
    fscanf(stat, "%d", &pid);
    char name[10];
    fscanf(stat, "%s", name);
    char status;
    fscanf(stat, " %c", &status);
    fclose(stat);
    free(stats);

    char* memoryFile = (char*)malloc(256 * sizeof(char));
    sprintf(memoryFile, "/proc/%d/statm", pid);
    FILE* memory = fopen(memoryFile, "r");
    int memorySize;
    fscanf(memory, "%d", &memorySize);
    fclose(memory);
    free(memoryFile);

    char* linkname = (char*)malloc(256 * sizeof(char));
    sprintf(linkname, "/proc/%d/exe", pid);
    char buf[256];
    int ret = readlink(linkname, buf, 256);
    buf[ret] = 0;
    char newbuf[256];
    if(strstr(buf, homeDirectory) !=NULL){
        int i=0,j=1;
        for(i=0;i<strlen(homeDirectory);i++){
            if(buf[i] != homeDirectory[i])
                break;
        }
        newbuf[0]='~';
        while(buf[i]!='\0')
            newbuf[j++] = buf[i++];
        strcpy(buf, newbuf);
    }

    printf("pid -- %d\n", pid);
    printf("Process Status -- %c\n", status);
    printf("memory -- %d\n", memorySize);
    printf("Executable Path -- %s\n", buf);
}