/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 22:16:45 by madaguen          #+#    #+#             */
/*   Updated: 2023/09/16 22:16:52 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_think_time(t_init *init)
{
	if (init->time_eat <= init->time_sleep)
		return (500);
	else
		return ((((init->time_eat - 1) - init->time_sleep) + 2) * 1000);
}

void	init_struct_philo(t_env *env, t_philo *philo, int i)
{
	philo->philo_id = i + 1;
	philo->data = &env->init;
	philo->last_meal = &env->last_meal[i];
	philo->last_meal->value = env->init.start_time;
	philo->meal_eaten = 0;
	philo->fork_right = &env->fork[i];
	if (i == env->init.nb_philo - 1)
		philo->fork_left = &env->fork[0];
	else
		philo->fork_left = &env->fork[i + 1];
}

void	set_death(t_env *env, int i)
{
	env->init.nb_philo = i;
	pthread_mutex_lock(&env->init.check_life->mutex);
	env->init.check_life->value = 0;
	pthread_mutex_unlock(&env->init.check_life->mutex);
}

int	verif_arg(char *s, int *nb)
{
	int	valid;

	valid = ft_atoi(s, nb);
	return (valid);
}

int	check_args(int ac, char **av, t_init *init)
{
	if (!verif_arg(av[1], &init->nb_philo))
		return (print_error("number of philosoph should be an int > 0\n"));
	if (!verif_arg(av[2], &init->time_die))
		return (print_error("time to die should be a valid int and > 0\n"));
	if (!verif_arg(av[3], &init->time_eat))
		return (print_error("time to eat should de a valid int and > 0\n"));
	if (!verif_arg(av[4], &init->time_sleep))
		return (print_error("time to sleep should de a valid int and > 0\n"));
	if (ac != 6)
		init->nb_meal = -1;
	else
	{
		if (!verif_arg(av[5], &init->nb_meal))
			return (print_error("number of meal should de an int and > 0\n"));
	}
	return (1);
}
