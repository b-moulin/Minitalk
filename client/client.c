#include "../header/minitalk.h"

void    send_bits(char c, int pid)
{
    int     i;

    i = 0;
    while (i < 8)
    {
        if ((c >> i & 1))
        {
            if (kill(pid, SIGUSR1) == -1)
                exit(1);
        }
        if (!(c >> i & 1))
        {
            if (kill(pid, SIGUSR2) == -1)
                exit(1);
        }
        i++;
        usleep(20);
    }
}

void    send_str(const char *str, int pid)
{
    int     i;

    i = 0;
    while (str && str[i])
    {
        send_bits(str[i], pid);
        i++;
    }
    send_bits(str[i], pid);
}

int     main(int argc, char **argv)
{
    int     pid;

    if (argc != 3)
    {
        printf("Error, bad number of arguments.\n");
        exit(1);
    }
    pid = ft_atoi(argv[1]);
    if (pid < 0)
    {
        printf("PID Error, please enter a valid PID.\n");
        exit (1);
    }
    send_str(argv[2], pid);
}