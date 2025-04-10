#include "philo.h"

void print(t_mutex *end, int id, char *message)
{
    char buffer[50];
    size_t now;
    int i;
 
    i = 0;
    // printf("ccocou print\n");
    if (end)
        pthread_mutex_lock(&end->mutex);
    if (!end || end->value == false)
    {
        now = get_time_from_start(false);
        i += itoa(buffer, now / 1000);
        i += itoa(buffer + i, id);
    	i += ft_strcpy(buffer + i, message);
        write(1, buffer, i);
    }
    if (end)
        pthread_mutex_unlock(&end->mutex);
}

// void print(t_mutex *end, int id, char *message)
// {
//     // char buffer[50];
//     size_t now;
//     // int i;
 
//     // i = 0;
//     // printf("ccocou print\n");
//     if (end)
//         pthread_mutex_lock(&end->mutex);
//     if (!end || end->value == false)
//     {
//         now = get_time_from_start(false);
//         // i += itoa(buffer, now / 1000);
//         // i += itoa(buffer + i, id);
//     	// i += ft_strcpy(buffer + i, message);
//         // write(1, buffer, i);
//         printf("%zu %d %s\n", now/1000, id, message);
//     }
//     if (end)
//         pthread_mutex_unlock(&end->mutex);
// }