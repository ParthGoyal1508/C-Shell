#include "headers.h"

int exitprogram(WINDOW *win)
{
    if ((wgetch(win) == 'q'))
    {
        wclear(win);
        return 1;
    }
    else
        return 0;
}

void nightswatch()
{
    char c;
    WINDOW *curr = initscr();
    WINDOW *win;
    FILE *fd1;
    win = newwin(800, 800, 1, 1);
    keypad(win, TRUE);
    noecho();
    curs_set(0);
    nodelay(win, 1);
    int start = time(NULL);
    int current = time(NULL);
    int prevcurrent = time(NULL);
    int timeInt = atoi(inputCommands[2]);
    int k = 0;
    char *cpuinfo;
    unsigned long bufsize = 0;
    char *nowbuffer;
    unsigned long nowbufsize = 0;

    if (totalCommands > 4 || totalCommands < 4)
    {
        printf("Please provide correct arguments\n");
    }
    else if (totalCommands == 4)
    {
        if (strcmp(inputCommands[1], "-n") != 0)
        {
            printf("Please provide correct arguments\n");
        }
        else
        {
            if (strcmp(inputCommands[3], "interrupt") == 0)
            {
                FILE *fd = fopen("/proc/interrupts", "r");
                getline(&cpuinfo, &bufsize, fd);
                fclose(fd);
                while (1)
                {
                    mvwaddstr(win, 0, 10, cpuinfo);
                    current = time(NULL);
                    if (exitprogram(win))
                        break;
                    if ((current - start) % timeInt == 0 && current != prevcurrent)
                    {
                        k += 1;
                        prevcurrent = current;
                        fd1 = fopen("/proc/interrupts", "r");
                        for (int i = 0; i < 3; i++)
                            getline(&nowbuffer, &nowbufsize, fd1);
                        mvwaddstr(win, k, 10, nowbuffer);
                        fclose(fd1);
                    }
                }
            }
            else if (strcmp(inputCommands[3], "dirty") == 0)
            {
                k = 0;
                while (1)
                {
                    current = time(NULL);
                    if (exitprogram(win))
                        break;
                    if ((current - start) % timeInt == 0 && current != prevcurrent)
                    {
                        k += 1;
                        prevcurrent = current;
                        fd1 = fopen("/proc/meminfo", "r");
                        for (int i = 0; i < 17; i++)
                            getline(&nowbuffer, &nowbufsize, fd1);
                        mvwaddstr(win, k, 10, nowbuffer);
                        fclose(fd1);
                    }
                }
            }
        }
    }
    noecho();
    curs_set(1);
    delwin(win);
    endwin();
    return;
}