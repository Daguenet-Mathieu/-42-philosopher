#include "philo.h"


void reverse(char *start, char *end)
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
        *ptr = nbr % 10 + '0';
        nbr /= 10;
        ptr++;
    }
    *ptr = ' ';
    *(ptr + 1) = 0;
    reverse(buffer, ptr - 1);
    return (ptr - buffer + 1);
}


// int itoa(char *buffer, size_t nbr)
// {
//     register char *ptr;
//     ptr = buffer;
    
//     if (nbr == 0)
//     {
//         *ptr = '0';
//         ptr++;
//         *ptr = ' ';
//         *(ptr + 1) = 0;
//         return 2;
//     }
    
//     while (nbr > 0)
//     {
//         size_t div;
//         int mod;
        
//         asm volatile (
//             "divq %3\n\t"
//             : "=a" (div), "=d" (mod)
//             : "a" (nbr), "r" ((size_t)10), "d" ((size_t)0)
//         );
        
//         *ptr = mod + '0';
//         nbr = div;
//         ptr++;
//     }
    
//     *ptr = ' ';
//     *(ptr + 1) = 0;
//     reverse(buffer, ptr - 1);
//     return (ptr - buffer + 1);
// }

// int itoa(char *buffer, size_t nbr)
// {
//     register char *ptr;
//     ptr = buffer;
    
//     if (nbr == 0)
//     {
//         *ptr = '0';
//         ptr++;
//         *ptr = ' ';
//         *(ptr + 1) = 0;
//         return 2;
//     }
    
//     while (nbr > 0)
//     {
//         size_t div;
//         int mod;
        
//         asm volatile (
//             "movq %[nbr], %%rax\n\t"   // rax = nbr (64-bit)
//             "xorq %%rdx, %%rdx\n\t"    // rdx = 0 (64-bit)
//             "movq $10, %%rcx\n\t"      // rcx = 10 (64-bit)
//             "divq %%rcx\n\t"           // rax = rax / rcx, rdx = rax % rcx
//             "movq %%rax, %[div]\n\t"   // div = rax
//             "movl %%edx, %[mod]\n\t"   // mod = edx (32-bit est suffisant pour le reste)
//             : [div] "=r" (div), [mod] "=r" (mod)
//             : [nbr] "r" (nbr)
//             : "rax", "rdx", "rcx"
//         );
        
//         *ptr = mod + '0';
//         nbr = div;
//         ptr++;
//     }
    
//     *ptr = ' ';
//     *(ptr + 1) = 0;
//     reverse(buffer, ptr - 1);
//     return (ptr - buffer + 1);
// }


// int itoa(char *buffer, size_t nbr)
// {
//     register char *ptr;
    
//     ptr = buffer;
//     if (nbr == 0)
//     {
//         *ptr = '0';
//         ptr++;
//     }
//     while (nbr > 0)
//     {
//         // printf(" pour nbr == %zu, %%10 == %zu, /10 == %zu\n", nbr, result.quotient, result.remainder);
//         *ptr = nbr % 10 + '0';
//         nbr /= 10;
//         ptr++;
//     }
//     *ptr = ' ';
//     *(ptr + 1) = 0;
//     reverse(buffer, ptr - 1);
//     return (ptr - buffer + 1);
// }

bool is_end(t_mutex *end)//check si c'est fini
{
	pthread_mutex_lock(&end->mutex);
    // printf("end val == %zu\n", end->value);
    if (end->value)
    {
    	pthread_mutex_unlock(&end->mutex);
        return (true);
    }
	pthread_mutex_unlock(&end->mutex);
    return (false);
}

static inline bool ft_usleep_loop(size_t const now, t_mutex *end, size_t sleep_time, size_t time)
{
    while (sleep_time >= time && get_time_from_start(false) - now <= sleep_time - time)
    {
        if (is_end(end) == true)
            return (false);
        usleep(time);
    }
    return (true);
}

bool  ft_usleep(size_t sleep_time, t_mutex *end)
{
    size_t const    now = get_time_from_start(false);
    int val[] = {1000000, 500000, 250000, 100000, 50000, 25000,10000, 5000, 1000};
    int const val_size = sizeof(val)/sizeof(int);
    int i;

    i = 0;
    while (i < val_size)
    {
        if (!ft_usleep_loop(now, end, sleep_time, val[i]))
            break ;
        i++;
    }
    while (get_time_from_start(false) - now <= sleep_time)
    {
        if (is_end(end) == true)
            return (false);
        usleep(500);
    }
    return (true);
}

bool take_forks(size_t id, pthread_mutex_t *left, pthread_mutex_t *right, t_mutex *end, size_t nb_philo)
{
    if (is_end(end))
    {
        return (false);
    }
    if (id == nb_philo)
        pthread_mutex_lock(right);
    else
        pthread_mutex_lock(left);
    print(end, id, "has taken a fork");
    if (is_end(end))
    {
        if (id == nb_philo)
            pthread_mutex_unlock(right);
        else
            pthread_mutex_unlock(left);
        return (false);
    }
    if (id == nb_philo)
        pthread_mutex_lock(left);
    else
        pthread_mutex_lock(right);
    print(end, id, "has taken a fork");
    return (true);
}

void release_forks(pthread_mutex_t *left, pthread_mutex_t *right)
{
    pthread_mutex_unlock(left);
    pthread_mutex_unlock(right);
}


bool do_think(int id, size_t think_time, t_mutex *end)//check type action?
{
    print(end, id, "is thinking");
    if (ft_usleep(think_time, end) == false)
        return (false);
    return (true);
}

bool do_eat(int id, size_t eat_time, t_mutex *end)
{
    print(end, id, "is eating");
    if (ft_usleep(eat_time, end) == false)
        return (false);
    return (true);
}

bool do_sleep(int id, size_t sleep_time, t_mutex *end)
{
    print(end, id, "is sleeping");
    if (ft_usleep(sleep_time, end) == false)
        return (false);
    return (true);
}

void    set_end(t_mutex *end, t_mutex *nb_full, int philo_nbr)
{
    int local_nb_full;
    pthread_mutex_lock(&nb_full->mutex);
    nb_full->value++;
    local_nb_full = nb_full->value;
    pthread_mutex_unlock(&nb_full->mutex);
    if (local_nb_full < philo_nbr)
        return ;
    pthread_mutex_lock(&end->mutex);
    end->value = 1;
    pthread_mutex_unlock(&end->mutex);
}

void start_actions(t_philo *p, t_data const data, int meal_eaten)
{
    while (is_end(p->end) == false)
    {
        if (take_forks(p->philo_id, &p->left_fork, p->right_fork, p->end, data.philo_nbr) == false)
            break ;
        pthread_mutex_lock(&p->data->last_meal);
        p->last_meal = get_time_from_start(false);
        pthread_mutex_unlock(&p->data->last_meal);
        if (do_eat(p->philo_id, data.eat_time, p->end) == false)
        {
            release_forks(&p->left_fork, p->right_fork);
            break ;
        }
        meal_eaten++;
        if (meal_eaten == data.meals_nb)
        {
            set_end(p->end, p->nb_full, data.philo_nbr);
        }
        release_forks(&p->left_fork, p->right_fork);
        if (do_sleep(p->philo_id, data.sleep_time, p->end) == false)
            break ;
        if (do_think(p->philo_id, p->think_time, p->end) == false)
            break ;
    }
}

void *routine(void *var)
{
    (void)var;
    // printf("couocudansle thrreads\n");
    //mutex start, end?//sleep impair time to eat et dernier si  impair time to eat *2
    t_philo *philo = (t_philo*)var;
    t_data data = *philo->data;
    //  printmessagefork; sleep time to die
    // printf("2couocudansle thrreads\n");
    pthread_mutex_lock(&philo->end->mutex);
    pthread_mutex_unlock(&philo->end->mutex);
    print(philo->end, philo->philo_id, "is thinking");
    if (philo->right_fork == &philo->left_fork)
    {
        print(philo->end, philo->philo_id, "has taken a fork"); 
        ft_usleep(data.death_time, philo->end);
        return (NULL);
    }
    if (!(philo->philo_id & 1))
        ft_usleep(data.eat_time, philo->end);
    if (data.philo_nbr & 1 && philo->philo_id == data.philo_nbr)
        ft_usleep(2 * data.eat_time, philo->end);
    start_actions(philo, data, 0);
    // printf("3couocudansle thrreads\n");
    
    return (NULL);
}
