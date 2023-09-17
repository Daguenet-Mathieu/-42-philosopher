/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 20:18:37 by madaguen          #+#    #+#             */
/*   Updated: 2023/09/16 01:39:55 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo, t_init init, int *index, t_env *env)
{
	t_ull	now;
	t_ull	last_meal;

	*index = 0;
	now = get_time();
	while (*index < init.nb_philo)
	{
		pthread_mutex_lock(&philo[*index].last_meal->mutex);
		last_meal = philo[*index].last_meal->value;
		pthread_mutex_unlock(&philo[*index].last_meal->mutex);
		if (last_meal == 0)
			last_meal = init.start_time;
		if (now > last_meal && (now - last_meal) > (t_ull)init.time_die)
		{
			pthread_mutex_lock(&env->check_life.mutex);
			env->check_life.value = 0;
			pthread_mutex_unlock(&env->check_life.mutex);
			return (0);
		}
		(*index)++;
	}
	return (2);
}

void	monitoring(t_env *env, t_philo *philo)
{
	int		full;
	int		index;
	t_ull	is_alive;

	full = 0;
	pthread_mutex_lock(&env->check_life.mutex);
	is_alive = env->check_life.value;
	pthread_mutex_unlock(&env->check_life.mutex);
	while (is_alive >= 2 && full < env->init.nb_philo)
	{
		pthread_mutex_lock(&env->full.mutex);
		full = env->full.value;
		pthread_mutex_unlock(&env->full.mutex);
		is_alive = check_death(philo, env->init, &index, env);
		if (is_alive <= 1)
			print("died", &philo[index]);
		else
			usleep(100);
	}
}
