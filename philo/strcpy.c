#include "philo.h"

int ft_strcpy(char buffer[], char const *const src)
{
    int i;

    i = 0;
    while (src[i])
    {
        buffer[i] = src[i];
        i++;
    }
    buffer[i] = '\n';
    i++;
    buffer[i] = 0;
    return (i);
}