#include "philo.h"

static void add_infos(t_init *philo_data, int infos[4])
{
	philo_data->philo_number = infos[0];
	philo_data->data.death_time = infos[1] * 1000;
	philo_data->data.eat_time = infos[2] * 1000;
	philo_data->data.sleep_time = infos[3] * 1000;
}

bool parse_args(t_init *philo_data, char const *const args[], int size)
{
	int res;
	int infos[4];
	int i;

	i = 0;
	while (i < 4)
	{
		if (ft_atoi(args[i], &res) == false || res <= 0)
			return (false);
		else
			infos[i] = res;
		i++;
	}
	philo_data->data.meals_nb = -1;
	if (size == 5)
	{
		if (ft_atoi(args[4], &res) == false || res <= 0)
			return (false);
		else
			philo_data->data.meals_nb = res;
	}
	add_infos(philo_data, infos);
	return (true);
}
