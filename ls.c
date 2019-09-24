#include "headers.h"

int match_ls_flag(char *comA, char *comB) {
    if (((strcmp(comA, "-l") == 0) && (strcmp(comB, "-a") == 0)) ||
        ((strcmp(comA, "-a") == 0) && (strcmp(comB, "-l") == 0)))
        return 1;
    else
        return 0;
}

int check_hiddenFile(char *directoryName) {
    if (directoryName[0] == '.')
        return 1;
    else
        return 0;
}

void checkfileType(struct stat sb) {
    switch (sb.st_mode & S_IFMT) {
        case S_IFBLK:
            printf("b");
            break;
        case S_IFCHR:
            printf("c");
            break;
        case S_IFDIR:
            printf("d");
            break;
        case S_IFIFO:
            printf("F");
            break;
        case S_IFLNK:
            printf("l");
            break;
        case S_IFREG:
            printf("-");
            break;
        case S_IFSOCK:
            printf("s");
            break;
        default:
            printf("u");
            break;
    }
}

void ls_listwise(struct dirent *directoryEntry, DIR *directory, char *flag) {
    while ((directoryEntry = readdir(directory)) != NULL) {
        if ((check_hiddenFile(directoryEntry->d_name) == 1) &&
            strcmp(flag, "-l") == 0) {
            continue;
        }
        struct stat st;
        stat(directoryEntry->d_name, &st);
        checkfileType(st);
        printf((st.st_mode & S_IRUSR) ? "r" : "-");
        printf((st.st_mode & S_IWUSR) ? "w" : "-");
        printf((st.st_mode & S_IXUSR) ? "x" : "-");
        printf((st.st_mode & S_IRGRP) ? "r" : "-");
        printf((st.st_mode & S_IWGRP) ? "w" : "-");
        printf((st.st_mode & S_IXGRP) ? "x" : "-");
        printf((st.st_mode & S_IROTH) ? "r" : "-");
        printf((st.st_mode & S_IWOTH) ? "w" : "-");
        printf((st.st_mode & S_IXOTH) ? "x" : "-");
        // number of linked hard-links
        printf(" %2lu", st.st_nlink);
        // name of the owner of the file
        printf(" %s", getpwuid(st.st_uid)->pw_name);
        // name of the group to which this file belongs to
        printf(" %s", getgrgid(st.st_gid)->gr_name);
        // size
        printf(" %7ld", st.st_size);
        // date
        struct tm *timeinfo =
            localtime(&st.st_ctime);  // or gmtime() depending on what you want
        char timevalue[256];
        strftime(timevalue, sizeof(timevalue), "%b %d %H:%M", timeinfo);
        printf(" %s", timevalue);
        // file name
        printf(" %s\n", directoryEntry->d_name);
    }
}

void ls(char directoryPath[256], char *flag) {
    struct dirent *directoryEntry;  // Pointer for directory entry

    // opendir() returns a pointer of DIR type.
    DIR *directory = opendir(directoryPath);

    if (directory == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Could not open given directory\n");
        return;
    }

    // list wise
    if (strcmp(flag, "-l") == 0 || strcmp(flag, "-al") == 0 ||
        strcmp(flag, "-la") == 0) {
        ls_listwise(directoryEntry, directory, flag);
        closedir(directory);
        return;
    }

    // for listing directories
    while ((directoryEntry = readdir(directory)) != NULL) {
        if (check_hiddenFile(directoryEntry->d_name) && strcmp(flag, "-a") != 0)
            continue;
        printf("%s\n", directoryEntry->d_name);
    }

    closedir(directory);
    return;
}

char *changeDirectoryPath(char *oldDirectoryPath) {
    int oldPathLength = strlen(oldDirectoryPath);
    char *newDirectoryPath = calloc(sizeof(char) * 256, sizeof(char) * 1);
    for (int i = 0, j = 0; i < oldPathLength; i++) {
        if (oldDirectoryPath[i] == '~') {
            for (int x = 0; x < strlen(homeDirectory); x++) {
                newDirectoryPath[j++] = homeDirectory[x];
            }
        } else {
            newDirectoryPath[j++] = oldDirectoryPath[i];
        }
    }

    static char copyPath[256];
    strcpy(copyPath, newDirectoryPath);
    free(newDirectoryPath);
    return copyPath;
}

void executelsCommand() {
    if (strcmp(inputCommands[0], "ls") == 0) {
        char *directoryPath = calloc(sizeof(char) * 256, sizeof(char) * 1);
        directoryPath[0] = '.';
        char *flag = calloc(sizeof(char) * 256, sizeof(char) * 1);
        flag[0] = '\0';
        if (totalCommands == 2) {
            if ((strcmp(inputCommands[1], "-l") == 0) ||
                (strcmp(inputCommands[1], "-a") == 0) ||
                (strcmp(inputCommands[1], "-al") == 0) ||
                (strcmp(inputCommands[1], "-la") == 0))
                strcpy(flag, inputCommands[1]);
            else
                strcpy(directoryPath, inputCommands[1]);
        } else if (totalCommands == 3) {
            if (match_ls_flag(inputCommands[1], inputCommands[2]))
                strcpy(flag, "-la");
            else {
                strcpy(flag, inputCommands[1]);
                strcpy(directoryPath, inputCommands[2]);
            }
        } else if (totalCommands == 4) {
            if (match_ls_flag(inputCommands[1], inputCommands[2])) {
                strcpy(flag, "-la");
                strcpy(directoryPath, inputCommands[3]);
            }
        }

        char *modifiedDirectoryPath = changeDirectoryPath(directoryPath);
        ls(modifiedDirectoryPath, flag);
        free(directoryPath);
        free(flag);
        return;
    }
    return;
}
