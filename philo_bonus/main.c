#include "philo.h"

size_t get_think_time(size_t sleep_time, size_t eat_time, int nb_philo)
{
	if (nb_philo & 1)
	{
		return ((eat_time - sleep_time) + eat_time + 500);
	}
	return ((eat_time - sleep_time) + 500);
	// if (sleep_time >= (eat_time))
	// 	return (3500);
	// return (eat_time - sleep_time + 3500);
}

void	check_full(t_data *data)
{
	int i;

	i = 0;
	while (i < data->philo_nbr)
	{
		// printf("dans check full sem eat == %p et %p\n", &data->meals_nb, data->meals_nb);
		sem_wait(data->meals_nb);
		// printf("un philo a assew mange !\n");
		i++;
	}
	// printf("tout les philos onet assew mange !\n");
	free(data->philo_pids);
	sem_close(data->print);
	sem_close(data->forks);
	sem_close(data->meals_nb);
	exit(0);
}

bool launch_philo(t_data *data)
{
	// printf("pid parent == %d\n", getpid());
	int i;
	pid_t pid;
	int const philo_pid_size = data->philo_nbr + (data->nbr_allowed_meals != -1);

	i = 0;
	data->think_time = get_think_time(data->sleep_time, data->eat_time, data->philo_nbr);

	data->philo_pids = malloc((data->philo_nbr + 1) * sizeof(pid_t));
	if (data->philo_pids == NULL)
	{
		write (2, ALLOC_ERROR, ft_strlen(ALLOC_ERROR));
		return (false);
	}
	//prendre le semaphore de depart
	// printf("\n");
	get_time_from_start(true);
	i = 0;
	int child = 0;
    sem_wait(data->print);
	while (i < data->philo_nbr)
	{
		// printf("un philo a ete creee pid ==%d\n", getpid());
		pid = fork();
		if (pid == -1)
		{
			write (2, FORK_ERROR, ft_strlen(ALLOC_ERROR));//kill les reussites
			return (false);
		}
		if (pid == 0)
		{
			// printf("ici c'est l'efamt\n");
			routine(data, i + 1);
			return (false);
		}
		child++;
		data->philo_pids[i] = pid;
		i++;
	}
	// printf("un monitor a ete creee pid ==%d\n", getpid());
	// printf("i == %d , philo nbr == %d\n", i, data->philo_nbr);
	if (i < philo_pid_size)
	{
		data->philo_pids[i] = fork();
		if (data->philo_pids[i] == -1)
		{
			write (2, FORK_ERROR, ft_strlen(ALLOC_ERROR));//killles reussites
			return (false);
		}
		else if (data->philo_pids[i] == 0)
		{
			// printf("ici c'est le monitoring\n");
			check_full(data);
			return (false);
		}
		child++;
	}
	// printf("nb child == %d\n", child);
    sem_post(data->print);
	// printf("temps pour creer les forks : %zu\n", get_time_from_start(false));
	//lacher le semaphore de depart
	return (true);
}

// void destroy_philo(t_data *data, int died)
// {
// 	int	i;
	
// 	i = 0;
// 	while (i < data->philo_nbr)
// 	{
// 		if (i != died)
// 			kill(data->philo_pids[i], SIGKILL);
// 		//kill tout le monde sauf le deja fini
// 		i++;
// 	}
// 	i = 0;
// 	//detruire les semaphores
// 	free(data->philo_pids);
// }

void monitoring(t_data *data)
{
	int i;
	int	ended_philo;
	int const philo_pid_size = data->philo_nbr + (data->nbr_allowed_meals != -1);
	

	i= 0;
	while (1)
	{
		if (i >= philo_pid_size)
			i = 0;
		if (waitpid(data->philo_pids[i], NULL, WNOHANG))//NULl ok pour status?
			break ;//si i < philonbr print la mort ? dans toutl es cas saisir sem print
		i++;
	}
	ended_philo = i;
	// printf("l'enfant nbr %d s'est fini \n", ended_philo);
	i = 0;
	while (i < philo_pid_size)
	{
		if (i != ended_philo)
			kill(data->philo_pids[i], SIGKILL);
		//kill tout le monde sauf le deja fini
		i++;
	}
	free(data->philo_pids);
	sem_close(data->print);
	sem_close(data->forks);
	sem_close(data->meals_nb);

}

int main(int argc, char const *const argv[])
{
	//penser a conditionner le hild monitor
    t_data	data;
	// int		died;
	// test_atoi();
	// test_itoa();
    if (argc < 5)
	{
        write(2, ARG_ERROR, ft_strlen(ARG_ERROR));
		return (1);
	}
	if (!parse_args(&data, argv + 1, argc - 1))
	{
        write(2, ARG_TYPE_ERROR, ft_strlen(ARG_TYPE_ERROR));
		return 1;
	}
	// printf("nb philo == %d, time to die == %lu, time to eat == %lu, time to sleep == %lu, nb meal == %d\n", philo_data.philo_number, philo_data.data.death_time, philo_data.data.eat_time, philo_data.data.sleep_time, philo_data.data.meals_nb);
	if (create_semaphores(&data) == false)//detruire les mutex qui ont reussi
		return (1);
	// printf("init success?\n");
	if (launch_philo(&data) == false)//resize le nb philo au nb de reussi
		return (1);
	// printf("couocu\n");
	monitoring(&data);
	// destroy_philo(&data, died);
	return (0);
}