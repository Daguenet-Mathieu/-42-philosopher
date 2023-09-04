/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 20:20:06 by madaguen          #+#    #+#             */
/*   Updated: 2023/06/30 20:20:08 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	int		sleep_time;
	int		current_time;
	int		is_alive;

	sleep_time = 0;
	if (!take_fork(philo))
	{
		usleep(philo->data->time_die * 1000);
		return ;
	}
	pthread_mutex_lock(&philo->last_meal->mutex);
	philo->last_meal->value = get_time();
	pthread_mutex_unlock(&philo->last_meal->mutex);
	print("is eating", philo);
	philo->meal_eaten += 1;
	usleep(philo->data->time_eat * 1000);
	release_fork(philo);
}

int	check_nb_meal(t_philo *philo)
{
	int	full;

	full = 0;
	pthread_mutex_lock(&philo->data->full->mutex);
	if (philo->meal_eaten == philo->data->nb_meal)
		philo->data->full->value += 1;
		full = philo->data->full->value;
	pthread_mutex_unlock(&philo->data->full->mutex);
	if (full == philo->data->nb_philo)
		return (0);
	return (1);
}

void	*in_thread(void *thread_info)
{
	int		is_alive;
	t_philo	*philo;
	philo = (t_philo *) thread_info;
	is_alive = 2;
	while (1)
	{	
		if (!(philo->philo_id & 1))
			usleep(500);
		pthread_mutex_lock(&philo->data->check_life->mutex);
		is_alive = philo->data->check_life->value;
		pthread_mutex_unlock(&philo->data->check_life->mutex);
		if (is_alive <= 1)
			break ;
		eating(philo);
		if (!check_nb_meal(philo))
			break ;
		print("is sleeping", philo);
		usleep(philo->data->time_sleep * 1000);
		print("is thinking", philo);
	}
	return (NULL);
}
