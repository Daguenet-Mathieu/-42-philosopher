
#include "philo.h"

t_ull   get_time()
{
    t_time  time;
    t_ull   now;

    gettimeofday(&time, NULL);
	now = time.tv_sec * 1000 + time.tv_usec / 1000;
    return (now);
}