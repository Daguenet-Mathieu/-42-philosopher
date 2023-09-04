/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 20:18:50 by madaguen          #+#    #+#             */
/*   Updated: 2023/06/30 20:18:53 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_mutex(void *mutex, char *s, t_philo *philo)
{
	pthread_mutex_lock(mutex);
	if (s)
		print(s, philo);
	return ;
}

void	release_mutex(void *mutex)
{
	pthread_mutex_unlock(mutex);
	return ;
}

int	take_fork(t_philo *philo)
{
	if ((philo->philo_id & 1))
		take_mutex(philo->fork_right, "has taken a fork", philo);
	else
		take_mutex(philo->fork_left, "has taken a fork", philo);
	if (philo->data->nb_philo == 1)
	{
		usleep(philo->data->time_die * 1000 + 100);
		return (release_mutex(philo->fork_right), 0);
	}
	if (!(philo->philo_id & 1))
		take_mutex(philo->fork_right, "has taken a fork", philo);
	else
		take_mutex(philo->fork_left, "has taken a fork", philo);
	return (1);
}

void	release_fork(t_philo *philo)
{
	if (!(philo->philo_id & 1))
		pthread_mutex_unlock(philo->fork_left);
	else
		pthread_mutex_unlock(philo->fork_right);
	usleep(50);
	if ((philo->philo_id & 1))
		pthread_mutex_unlock(philo->fork_left);
	else
		pthread_mutex_unlock(philo->fork_right);
}
