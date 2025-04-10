#include "philo.h"

int ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
    {
        i++;
    }
    return (s1[i] - s2[i]);
}

void	print(t_data *data, size_t last_meal, int id, char *message)
{
    char buffer[50];
    size_t now;
    int i;
 (void)data;
 (void)last_meal;
    i = 0;
    sem_wait(data->print);
    // printf("ccocou print\n");
    //xait sem
    //fct is end
    now = get_time_from_start(false);
    i += itoa(buffer, now / 1000);
    i += itoa(buffer + i, id);
    i += ft_strcpy(buffer + i, message);
    write(1, buffer, i);
    if (ft_strcmp(message, "died"))
        sem_post(data->print);
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