#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

volatile sig_atomic_t g_bit_acknowledged = 0;

void ack_handler(int sig)
{
    (void)sig;
    g_bit_acknowledged = 1;
}

void send_signal(int pid, unsigned char character)
{
    int i;

    i = 0;
    while(i < 8)
    {
        g_bit_acknowledget = 0;

        if((character >> i) & 1)
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        while(!g_bit_acknowledged)
            usleep(100);

        i++;
    }
}

int main(int ac, char *av[])
{
    pid_t server_pid;
    const char *message;
    int         i;
    struct sigaction sa;

    if(ac != 3)
    {
         printf("Usage: %s <pid> <message>\n", av[0]);
         exit(0);
    }
    sa.sa_handler = ack_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGURSR1, &sa, NULL);
    server_pid = atoi(av[1]);
    message = av[2];
    i = 0;
    while(message[i])
    {
        send_signal(server_pid, message[i]);
        i++
    }
    send_signal(server_pid, '\0');
    usleep(1000);
    return (0);
}
