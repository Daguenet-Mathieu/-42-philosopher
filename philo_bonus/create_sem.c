#include "philo.h"

bool create_semaphores(t_data *data)
{
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("meals_nb");
	data->forks = sem_open("forks", O_CREAT, 0644, data->philo_nbr);
	if (data->forks == SEM_FAILED){
		printf("fail forks\n");
		return (false);
	}
	sem_unlink("forks");
	data->print = sem_open("print", O_CREAT, 0644, 1);
	if (data->print == SEM_FAILED)
	{
		printf("fail print\n");
		sem_close(data->forks);
		return (false);
	}
	sem_unlink("print");
	data->meals_nb = sem_open("meals_nb", O_CREAT, 0644, 0);
	if (data->meals_nb == SEM_FAILED)
	{
		printf("fail meal\n");
		sem_close(data->forks);
		sem_close(data->print);
		return (false);
	}
	sem_unlink("meals_nb");
	return (true);
}
