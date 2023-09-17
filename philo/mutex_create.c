/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_ceate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 22:20:21 by madaguen          #+#    #+#             */
/*   Updated: 2023/09/16 22:46:22 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_meal(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->init.nb_philo)
	{
		if (pthread_mutex_init(&env->last_meal[i].mutex, NULL))
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

int	get_mutex(t_philo *philo, t_env *env)
{
	if (pthread_mutex_init(&env->check_life.mutex, NULL))
		return (del_fork(env->init.nb_philo, env), \
			del_meal(env->init.nb_philo, env), \
			free(env->fork), free(philo), free(env->last_meal), 0);
	if (pthread_mutex_init(&env->full.mutex, NULL))
		return (del_fork(env->init.nb_philo, env), \
			del_meal(env->init.nb_philo, env), free(env->fork), \
			pthread_mutex_destroy(&env->check_life.mutex), free(env->last_meal),
			free(philo), 0);
	if (pthread_mutex_init(&env->start, NULL))
		return (del_fork(env->init.nb_philo, env), \
			del_meal(env->init.nb_philo, env), \
			free(env->fork), pthread_mutex_destroy(&env->start), \
			pthread_mutex_destroy(&env->check_life.mutex), \
			free(env->last_meal), free(philo), 0);
	return (1);
}
