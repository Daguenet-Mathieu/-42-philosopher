/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 20:18:10 by madaguen          #+#    #+#             */
/*   Updated: 2023/06/30 20:18:13 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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


void	init_struct_philo(t_env *env, t_philo *philo, int i)
{
	philo->philo_id = i + 1;
	philo->data = env->init;
	philo->check_life = &env->check_life;
	philo->last_meal = &env->last_meal[i];
	philo->last_meal->value = env->init.start_time;
	philo->meal_eaten = 0;
	philo->fork_right = &env->fork[i];
	if (i == env->init.nb_philo - 1)
		philo->fork_left = &env->fork[0];
	else
		philo->fork_left = &env->fork[i + 1];
}

int	init_philo(t_env *env, t_philo *philo)
{
	int		i;
	t_time	time;
	t_ull	current_time;

	i = 0;
	gettimeofday(&time, NULL);
	current_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	env->init.start_time = current_time;
	while (i < env->init.nb_philo)
	{
		init_struct_philo(env, &philo[i], i);
		if (fork() > 0)
		{
			routine(env, philo, i);
			exit(0);
		}
			return (0);
		i++;
	}
	return (1);
}
