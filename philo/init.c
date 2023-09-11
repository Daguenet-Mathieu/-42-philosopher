/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 20:18:10 by madaguen          #+#    #+#             */
/*   Updated: 2023/09/11 17:50:16 by madaguen         ###   ########.fr       */
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

int create_meal(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->init.nb_philo)
	{
		if (pthread_mutex_init(&env->fork[i], NULL))
			return (i);
		i++;
	}
	return (-1);
}

int	create_fork(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->init.nb_philo)
	{
		if (pthread_mutex_init(&env->fork[i], NULL))
			return (i);
		i++;
	}
	return (-1);
}

void	del_fork(int i, t_env *env)
{
	while (i >= 0)
	{
		pthread_mutex_destroy(&env->fork[i]);
		i--;
	}
}

void	del_meal(int i, t_env *env)
{
	while (i >= 0)
	{
		pthread_mutex_destroy(&env->fork[i]);
		i--;
	}
}

int	init_mutex(t_env *env, t_philo **philo)
{
	int	i;

	i = 0;
	*philo = malloc(env->init.nb_philo * sizeof(t_philo));
	if (!*philo)
		return (print_error("alloc philo failed\n"), 0);
	memset(*philo, 0, env->init.nb_philo * sizeof(t_philo));
	env->fork = malloc(sizeof(pthread_mutex_t) * env->init.nb_philo);
	if (!env->fork)
		return (free(*philo), print_error("alloc fork failed\n"), 0);
	env->last_meal = malloc(sizeof(t_mutex) * env->init.nb_philo);
	if (!env->last_meal)
		return (free(*philo), free(env->fork), print_error("alloc meal\n"), 0);
	i = create_fork(env);
	if (i != -1)
		return (free(*philo), free(env->last_meal), free(env->fork), 0);
	i = create_meal(env);
	if (i != -1)
		return (free(*philo), free(env->last_meal), free(env->fork), del_meal(i, env), 0);
	if (pthread_mutex_init(&env->check_life.mutex, NULL))
		return (del_fork(env->init.nb_philo, env), del_meal(env->init.nb_philo, env), free(env->fork), free(philo), free(env->last_meal),0);
	if (pthread_mutex_init(&env->full.mutex, NULL))
		return (del_fork(env->init.nb_philo, env), del_meal(env->init.nb_philo, env), free(env->fork), pthread_mutex_destroy(&env->check_life.mutex), free(env->last_meal),free(philo), 0);
	env->check_life.value = 2;
	env->init.check_life = &env->check_life;
	env->full.value = 0;
	env->init.full = &env->full;
	return (1);
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

int	init_philo(t_env *env, t_philo *philo)
{
	int		i;

	i = 0;
	env->init.start_time = get_time();
	while (i < env->init.nb_philo)
	{
		init_struct_philo(env, &philo[i], i);
	//	printf("data philo dans juste avant == %p\n", philo[i].data);
	//	printf("data env dans juste avant == %p\n", &env->check_life);
	//	printf("data check_life de philo dans juste avant == %p\n", philo[i].data->check_life);
	//	printf("data check life youhou c'eat pas printf c'est moi le debile??? philo[i] == %p\n", &philo[i]);
		if (pthread_create(&philo[i].thread_id, NULL, in_thread, &philo[i]))
			return (i);
	//	printf("data philo dans juste apres == %p\n", philo[i].data);
		i++;
	}
	return (0);
}
