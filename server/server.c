#include "../header/minitalk.h"

void    use_signal(int sig)
{
    static  int     nb = 0;
    static  char    c = 0;


    if (sig == SIGINT)
        exit(0);
    else if (sig == SIGUSR1)
    {
        c |= (1 << nb);
    }
    else if (sig == SIGUSR2)
    {
        c |= (0 << nb);
    }
    if (nb == 7)
    {
        if (c)
            printf("%c", c);
        if (!c)
            printf("\n");
        nb = 0;
        c = 0;
    }
    else 
        nb = nb + 1;
}

int     main()
{
    int     pid;
    pid = getpid();
    if (pid < 0)
    {
        printf("Error, pid not generated\n");
        exit(1);
    }
    printf("PID %d\n", pid);

    signal(SIGUSR1, use_signal);
    signal(SIGUSR2, use_signal);
    signal(SIGINT, use_signal);
    
    while (1)
        pause();
}