#include <stdio.h>
# include <stdlib.h>

static char *find_path(char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        if (ft_strncmp(env[i], "PATH=", 5) == 0)
            return (env[i] + 5);
        i++;
    }
    return (NULL);
}

int main(int argc, char **argv, char **env)
{
    (void) argc;
    (void) argv;
    char **tab;

    tab = ft_split("Hello World", ' ');
    return (0);
}