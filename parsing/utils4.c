#include "minishell.h"

volatile sig_atomic_t g_interrupt = 0;

void gestionnaire2(int sig)
{
    (void)sig;
    g_interrupt = 1;
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void config_signals2(void)
{
    struct sigaction sa;
    sa.sa_handler = gestionnaire2;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGQUIT, &sa, NULL);
    sa.sa_handler = SIG_IGN;
    sigaction(SIGQUIT, &sa, NULL);
}

void checkif2(char *str, char c)
{
    struct termios term;
    int i;
    int count;
    char *line;
    
    count = 0;
    i = 0;
    while(str[i] != '\0')
    {
        if (str[i] == c)
        {
            count++;
        }
        i++;
    }
    
    if (count % 2 != 0)
    {
        g_interrupt = 0;
        signal(SIGINT, gestionnaire2);
        
        while(!g_interrupt)
        {
            if (c == 1)
                break;
            tcgetattr(STDIN_FILENO, &term);
            term.c_lflag &= ~ECHOCTL;
            tcsetattr(STDIN_FILENO, TCSANOW, &term);
            line = readline("> ");
            if (g_interrupt)
            {
                if (line)
                    free(line);
                break;
            }
            if (line == NULL)
            {
                printf("\n");
                break;
            }
            if (line[0] == '\0')
            {
                free(line);
                continue;
            }
            free(line);
        }
    }
}
