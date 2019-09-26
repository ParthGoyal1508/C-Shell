#ifndef HEAD
#define HEAD
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <sys/utsname.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <pwd.h>
#include <grp.h>
#include <curses.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include <fcntl.h>
#include <sys/sysmacros.h>
#include "display.c"
#include "builtin-commands.c"
#include "input.c"
#include "history.c"
#include "ls.c"
#include "pinfo.c"
#include "nightswatch.c"
#include "envar.c"
#include "signal.h"
#endif

char homeDirectory[1024];
struct utsname unameData;
char *username;

int totalCommands;
char *inputCommands[256];
int processType; //0 for foreground and 1 for background
int redirection; //0 for not redirected and 1 for redirection

int childProcess[1000];
int noOfChildProcess;

char* historyArray[20];
int noOfhistoryCommands;

char* commandArray[256];
