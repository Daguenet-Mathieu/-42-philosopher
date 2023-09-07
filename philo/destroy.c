/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 20:17:59 by madaguen          #+#    #+#             */
/*   Updated: 2023/06/30 20:18:02 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_thread(t_init init, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < init.nb_philo)
	{
		pthread_join(philo[i].thread_id, NULL);
		i++;
	}
}

void	destroy_mutex(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->init.nb_philo)
	{
		pthread_mutex_destroy(&env->fork[i]);
		pthread_mutex_destroy(&env->last_meal[i].mutex);
		i++;
	}
	pthread_mutex_destroy(&env->check_life.mutex);
	pthread_mutex_destroy(&env->full.mutex);
}

void	destroy_env(t_env *env, t_philo *philo)
{
	join_thread(env->init, philo);
	destroy_mutex(env);
	free(philo);
	free(env->fork);
	free(env->last_meal);
}
