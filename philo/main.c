#include "philo.h"

size_t get_think_time(size_t sleep_time, size_t eat_time, size_t nb_philo)
{
	size_t margin_odd_even;

	margin_odd_even = 500;
	if (nb_philo & 1)
		margin_odd_even = 1500;
	if (sleep_time >= (eat_time))
		return (margin_odd_even);
	return (eat_time - sleep_time + margin_odd_even);
}

void launch_philo(t_init *p)
{
	int i;
	size_t const think_time = get_think_time(p->data.sleep_time, p->data.eat_time, p->philo_number);

	i = 0;
	// printf("think time == %zu\n", think_time);
	pthread_mutex_lock(&p->end.mutex);
	while (i < p->philo_number)
	{
		p->philos[i].philo_id = i + 1;
		p->philos[i].last_meal = 0;
		p->philos[i].data = &p->data;
		p->philos[i].think_time = think_time;

		// printf("id : %d time : %zu, ", i + 1, p->philos[i].think_time);
		if (pthread_create(&p->philos[i].thread_id, NULL, routine, &p->philos[i]))
		{
			p->philo_number = i;
			return ;
		}
		i++;
	}
	// printf("\n");
	get_time_from_start(true);
	pthread_mutex_unlock(&p->end.mutex);
}

void	monitoring(t_init *philo_data)
{
	int i = 0;
	size_t last_meal;
	size_t const death_time = philo_data->data.death_time;
	size_t now;


	while (is_end(&philo_data->end) == false)
	{
		i = 0;
		pthread_mutex_lock(&philo_data->data.last_meal);
		now = get_time_from_start(false);
		while (i < philo_data->philo_number)
		{
			last_meal = philo_data->philos[i].last_meal;
			// printf("id == %d\n", i + 1);
			// dprintf(2, "time form last meal == %zu\n", now - last_meal);
			// dprintf(2, "last meal == %zu\n", last_meal);
			// dprintf(2, "now == %zu\n", now);
			// dprintf(2, "death time == %zu\n", death_time);
			// printf("res == %d\n", now - last_meal >  death_time);
			if (now > last_meal && now - last_meal > death_time)
			{
				pthread_mutex_lock(&philo_data->end.mutex);
				print(NULL, i + 1, "died");
				philo_data->end.value = 1;
				pthread_mutex_unlock(&philo_data->end.mutex);
				// pthread_mutex_unlock(&philo_data->philos[i].last_meal.mutex);
				pthread_mutex_unlock(&philo_data->data.last_meal);
				return ;
			}
			i++;
		}
		pthread_mutex_unlock(&philo_data->data.last_meal);
		usleep(10);//100?500?
	}
}

void destroy_philo(t_init *philo_data)
{
	int	i;
	
	i = 0;
	while (i < philo_data->philo_number)
	{
		pthread_join(philo_data->philos[i].thread_id, NULL);
		i++;
	}
	i = 0;
	while (i < philo_data->philo_number)
	{
		pthread_mutex_destroy(&philo_data->philos[i].left_fork);
		i++;
	}
	pthread_mutex_destroy(&philo_data->end.mutex);
	pthread_mutex_destroy(&philo_data->data.last_meal);
	free(philo_data->philos);
}

int main(int argc, char const *const argv[])
{
    t_init philo_data;

	// test_atoi();
	// test_itoa();
    if (argc < 5)
	{
        write(2, ARG_ERROR, ft_strlen(ARG_ERROR));
		return (1);
	}
	if (!parse_args(&philo_data, argv + 1, argc - 1))
	{
        write(2, ARG_TYPE_ERROR, ft_strlen(ARG_TYPE_ERROR));
		return 1;
	}
	// printf("nb philo == %d, time to die == %lu, time to eat == %lu, time to sleep == %lu, nb meal == %d\n", philo_data.philo_number, philo_data.data.death_time, philo_data.data.eat_time, philo_data.data.sleep_time, philo_data.data.meals_nb);
	philo_data.data.philo_nbr = philo_data.philo_number;
	if (create_mutex(&philo_data) == false)//detruire les mutex qui ont reussi
		return (1);
	launch_philo(&philo_data);//resize le nb philo au nb de reussi
	monitoring(&philo_data);
	destroy_philo(&philo_data);
	return (0);
}