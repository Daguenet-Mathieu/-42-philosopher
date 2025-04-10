#include "philo.h"

static void add_infos(t_data *data, int infos[4])
{
	data->philo_nbr = infos[0];
	data->death_time = infos[1] * 1000;
	data->eat_time = infos[2] * 1000;
	data->sleep_time = infos[3] * 1000;
}

bool parse_args(t_data *data, char const *const args[], int size)
{
	int res;
	int infos[4];
	int i;
//proteger les valeurs negatives
	i = 0;
	while (i < 4)
	{
		if (ft_atoi(args[i], &res) == false || res <= 0)
			return (false);
		else
			infos[i] = res;
		i++;
	}
	data->nbr_allowed_meals = -1;
	if (size == 5)
	{
		if (ft_atoi(args[4], &res) == false || res <= 0)
			return (false);
		else
			data->nbr_allowed_meals = res;
	}
	add_infos(data, infos);
	return (true);
}
