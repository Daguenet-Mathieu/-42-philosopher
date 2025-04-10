#include "philo.h"


inline void reverse(char *start, char *end)
{
    char tmp;

    while (end > start)
    {
        tmp = *start;
        *start = *end;
        *end = tmp;
        start++;
        end--;
    }
}

int itoa(char *buffer, size_t nbr)
{
    register char *ptr;
    
    ptr = buffer;
    if (nbr == 0)
    {
        *ptr = '0';
        ptr++;
    }
    while (nbr > 0)
    {
        // printf(" pour nbr == %zu, %%10 == %zu, /10 == %zu\n", nbr, result.quotient, result.remainder);
        *ptr = nbr % 10 + '0';

        nbr /= 10;
        ptr++;
    }
    *ptr = ' ';
    *(ptr + 1) = 0;
    reverse(buffer, ptr - 1);
    return (ptr - buffer + 1);
}

void is_end(t_data *data, size_t last_meal, int id)//check si c'est fini /sem
{
    // printf("end val == %zu\n", end->value);
//   return (true);
    // sem_wait(data->print);
    // dprintf(2, "id == %d, last meal == %zu, death_time== %zu, diff == %zu, calc res == %zu , now ==%zu\n", id, last_meal, data->death_time, get_time_from_start(false) - last_meal, last_meal + data->death_time, get_time_from_start(false));
    // sem_post(data->print);
    if (get_time_from_start(false) > last_meal + data->death_time)
    {
        print(data, last_meal, id, "died");//post fourchettes?
        free(data->philo_pids);
        sem_close(data->print);
        sem_close(data->forks);
        sem_close(data->meals_nb);    
        exit(0);//free_philo (philo);free et close + exit
    }
//calcul fin si fin wait se fin
}

// static inline void ft_usleep_loop(size_t const now, t_data *data, size_t last_meal, size_t sleep_time, size_t time, int id)
// {
//     while (sleep_time >= time && get_time_from_start(false) - now <= sleep_time - time)
//     {
//         is_end(data, last_meal, id);
//         if (death_time - last)
//         usleep(time);
//     }
// }


size_t get_sleep_duration(size_t const now, size_t const death_time, size_t const end_time)
{
    size_t const time_remaining = end_time - now;
    size_t const time_to_death = death_time - now;
    size_t sleep_duration;

    if (time_remaining < time_to_death)
        sleep_duration = time_remaining;
    else
    sleep_duration = time_to_death;
    // if (sleep_duration < 1000)
    //     return (1000);
    // else
    return (sleep_duration);
        
    
}

void ft_usleep(t_data *data, size_t last_meal, size_t sleep_time, int id)
{
    size_t now = get_time_from_start(false);
    size_t const end_time = now + sleep_time;
    size_t const death_time = last_meal + data->death_time;
    size_t sleep_duration;

    
    while (now < end_time)
    {
        // Vérifier si le philosophe est mort
        if (now > death_time)
        {
            print(data, last_meal, id, "died");
            free(data->philo_pids);
            sem_close(data->print);
            sem_close(data->forks);
            sem_close(data->meals_nb);
            exit(0);
        }
        
        sleep_duration = get_sleep_duration(now, death_time, end_time);
    
    if (sleep_duration > 0)
        usleep(sleep_duration);
    now = get_time_from_start(false);
}
}

// void  ft_usleep(t_data *data, size_t last_meal, size_t sleep_time, int id)
// {
//     size_t const    now = get_time_from_start(false);
//     // int val[] = {1000000, 500000, 250000, 100000, 50000, 25000,10000, 5000, 1000};
//     // int const val_size = sizeof(val)/sizeof(int);
//     // int i;
    
//     // i = 0;
//     // while (i < val_size)
//     // {
//     //     ft_usleep_loop(now, data, last_meal, sleep_time, val[i], id);
//     //     i++;
//     // }
//     // while (get_time_from_start(false) - now <= sleep_time)
//     // {
//     //     is_end(data, last_meal, id);
//     //     usleep(500);
//     // }
//     while (get_time_from_start(false) - now <= sleep_time)
//     {
//         is_end(data, last_meal, id);
//         usleep(800);
//     }
// }
//probleme 199 ->196 ->199? augenter le think?
bool take_forks(size_t id, t_data *data, size_t last_meal)
{
    is_end(data, last_meal, id);
    sem_wait(data->forks);
    // print(data, last_meal, id, "a pris la fourchette");
    print(data, last_meal, id, "has taken a fork");
    is_end(data, last_meal, id);//probleme relachement fourchette ou pas? testster comme ca
    // print(data, last_meal, id, "attend la 2eme fourchette");
    sem_wait(data->forks);
    // print(data, last_meal, id, "a pris la 2eme fourchette");
    is_end(data, last_meal, id);
    print(data, last_meal, id, "has taken a fork");
    return (true);
}

void release_forks(size_t id, t_data *data, size_t last_meal)
{
    // int value;
    (void) data;
    (void) last_meal;
    (void) id;
    // sem_getvalue(data->forks, &value);
    // printf("sem value == %d\n", value);
    sem_post(data->forks);
    // print(data, last_meal, id, "a lache la fourcehtte");
    // sem_getvalue(data->forks, &value);
    // printf("sem value == %d\n", value);
    sem_post(data->forks);
    // print(data, last_meal, id, "a lache la fourcehtte");

}


void do_think(t_data *data, int id, size_t last_meal)//check type action?
{
    is_end(data, last_meal, id);
    print(data, last_meal, id, "is thinking");
    ft_usleep(data, last_meal, data->think_time, id);
}

void do_eat(t_data *data, int id, size_t *last_meal)
{
    is_end(data, *last_meal, id);
    print(data, *last_meal, id, "is eating");
    *last_meal = get_time_from_start(false);
    ft_usleep(data, *last_meal, data->eat_time, id);
}

void do_sleep(t_data *data, int id, size_t last_meal)
{
    is_end(data, last_meal, id);
    print(data, last_meal, id, "is sleeping");
    ft_usleep(data, last_meal, data->sleep_time, id);
}

void start_actions(int id, t_data *data, int meal_eaten)//chck sa propre mort en continue
{
    size_t last_meal;

    last_meal = 0;
    while (1)
    {
        take_forks(id, data, last_meal);
        do_eat(data, id, &last_meal);
        meal_eaten++;
        if (meal_eaten == data->nbr_allowed_meals)// pas de val juste sem post
        {
            // printf("sem eat == %p et %p\n", &data->meals_nb, data->meals_nb);
            sem_post(data->meals_nb);
        }
        release_forks(id, data, last_meal);
        do_sleep(data, id, last_meal);
        do_think(data, id, last_meal);
    }
    // printf("fon du monitorin pour : %d\n", id);
}

void    routine(t_data *data, int id)
{
    //post fourchette et wait sem start/end
    //post sem start 
    size_t last_meal;

    last_meal = 0;
    // printf("sem fourchete == %p\n", data->forks);
    sem_wait(data->print);
    sem_post(data->print);
    get_time_from_start(true);
    print(data, last_meal, id, "is thinking");
    if (data->philo_nbr == 1)
    {
        print(data, last_meal, id, "has taken a fork"); 
        ft_usleep(data, last_meal, data->death_time, id);
        print(data, last_meal, id, "died");
        exit (0);
    }
    if (!(id & 1))
        ft_usleep(data, last_meal, data->eat_time, id);
    if (data->philo_nbr & 1 && id == data->philo_nbr)
        ft_usleep(data, last_meal, data->eat_time * 2, id);
    start_actions(id, data, last_meal);
}
