/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 20:18:10 by madaguen          #+#    #+#             */
/*   Updated: 2023/09/16 22:46:10 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		pthread_mutex_destroy(&env->last_meal[i].mutex);
		i--;
	}
}

void	add_to_data(t_env *env)
{
	env->check_life.value = 2;
	env->init.check_life = &env->check_life;
	env->full.value = 0;
	env->init.start = &env->start;
	env->init.full = &env->full;
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
		return (free(*philo), free(env->last_meal), free(env->fork), \
			del_meal(i, env), 0);
	if (!get_mutex(*philo, env))
		return (0);
	add_to_data(env);
	return (1);
}

int	init_philo(t_env *env, t_philo *philo)
{
	int		i;

	i = 0;
	pthread_mutex_lock(env->init.start);
	env->init.start_time = 0;
	env->init.time_think = get_think_time(&env->init);
	while (i < env->init.nb_philo)
	{
		init_struct_philo(env, &philo[i], i);
		if (pthread_create(&philo[i].thread_id, NULL, in_thread, &philo[i]))
		{
			print_error("fail create thread\n");
			set_death(env, i);
			break ;
		}
		i++;
	}
	env->init.start_time = get_time();
	pthread_mutex_unlock(env->init.start);
	usleep(30000);
	return (0);
}
