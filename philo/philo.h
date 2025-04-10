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

# define ARG_ERROR "Error: Incorrect number of arguments.\n\
\tUsage: ./philo number_of_philosophers time_to_die time_to_eat\
 time_to_sleep [optional: number_of_meals]\n"

 #define ARG_TYPE_ERROR "Error: Incorrect argument type.\
All arguments must be positive integers, \
within the range of the maximum value of an int.\n"
  

typedef struct timeval	t_time;

typedef struct s_mutex
{
	size_t			value;
	pthread_mutex_t	mutex;
}t_mutex;

typedef struct s_data
{
	size_t	death_time;
	size_t	eat_time;
	size_t	sleep_time;
	size_t	start_time;
	int		meals_nb;
	int		philo_nbr;
	pthread_mutex_t	last_meal;
}t_data;

typedef struct s_philo
{
	t_mutex	*nb_full;
	t_mutex	*end;
	pthread_mutex_t	left_fork;
	pthread_mutex_t *right_fork;
	size_t think_time;
	t_data	*data;
	int philo_id;
	size_t	last_meal;
	// size_t last_meal;
	pthread_t thread_id;
	
}t_philo;

typedef struct s_init
{
	// pthread_mutex_t *forks;
	// pthread_mutex_t *last_meal;
	t_philo	*philos;
	t_data	data;
	t_mutex	nb_full;
	t_mutex	end;
	int		philo_number;
}t_init;



//util a delete du .h
int	itoa(char buffer[], size_t nbr);

//string util
int		ft_strlen(char *str);
int	ft_strcpy(char buffer[], char const *const src);

//parsing
bool	ft_atoi(char const *const str, int *const res);
bool	parse_args(t_init *philo_data, char const *const args[], int size);

//print
void	print(t_mutex *end, int id, char *message);

//time
size_t	get_time_from_start(bool init);

//init
bool create_mutex(t_init *philo_data);

void *routine(void *var);

bool is_end(t_mutex *end);

void reverse(char *start, char *end);

size_t do_operation(size_t *nbr, size_t limit, size_t add);

#endif