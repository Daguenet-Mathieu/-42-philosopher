#include "philo.h"

bool create_mutex(t_init *philo_data)
{
	int i;

	i = 0;
	philo_data->philos = malloc(sizeof(t_philo) * philo_data->philo_number);
	if (!philo_data->philos)
		return (false);
	if (pthread_mutex_init(&philo_data->end.mutex, NULL))
		; //proteger
	if (pthread_mutex_init(&philo_data->nb_full.mutex, NULL))
		; //proteger
	philo_data->end.value = 0;
	philo_data->nb_full.value = 0;
	if (pthread_mutex_init(&philo_data->data.last_meal, NULL))
		return (false); //proteger
	while (i < philo_data->philo_number)
	{
		if (pthread_mutex_init(&philo_data->philos[i].left_fork, NULL))
			break ; //proteger
		philo_data->philos[i].last_meal = 0;
		philo_data->philos[i].nb_full = &philo_data->nb_full;
		philo_data->philos[i].end = &philo_data->end;
		i++;
	}
	i = 0;
	while (i < philo_data->philo_number - 1)
	{
		philo_data->philos[i].right_fork = &philo_data->philos[i + 1].left_fork;
		i++;
	}
	philo_data->philos[i].right_fork = &philo_data->philos[0].left_fork;
	//ai i inf anb philo proteger echec
	return (true);
}
