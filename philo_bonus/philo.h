#ifndef PHILO_H
# define PHILO_H
# include <limits.h>

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
//# include <string.h> //?
# include <limits.h>
# include <stdbool.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h> 

# define ARG_ERROR "Error: Incorrect number of arguments.\n\
Usage: ./philo number_of_philosophers time_to_die time_to_eat\
 time_to_sleep [optional: number_of_meals]\n"

 #define ARG_TYPE_ERROR "Error: Incorrect argument type.\n\
 All arguments must be positive integers, \
 within the range of the maximum value of an int.\n"
  
# define ALLOC_ERROR "failed to alloc required memory\n"

# define FORK_ERROR "failed to init all philosophers in current environement\n"


typedef struct timeval	t_time;

typedef struct s_data
{
	size_t	death_time;
	size_t	eat_time;
	size_t	sleep_time;
	size_t	think_time;
	int		nbr_allowed_meals;
	int		philo_nbr;
	sem_t *forks;
	sem_t *print;
	sem_t *meals_nb;
	pid_t *philo_pids;
}t_data;

//util a delete du .h
int	itoa(char buffer[], size_t nbr);

//string util
int		ft_strlen(char *str);
int		ft_strcpy(char buffer[], char const *const src);

//parsing
bool	ft_atoi(char const *const str, int *const res);
bool	parse_args(t_data *data, char const *const args[], int size);

//print
void	print(t_data *data, size_t last_meal, int id, char *message);

//time
size_t	get_time_from_start(bool init);

//init
void    routine(t_data *data, int id);

void is_end(t_data *data, size_t last_meal, int id);

void reverse(char *start, char *end);

size_t do_operation(size_t *nbr, size_t limit, size_t add);

bool create_semaphores(t_data *data);

#endif