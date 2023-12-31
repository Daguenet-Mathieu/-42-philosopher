/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 20:20:06 by madaguen          #+#    #+#             */
/*   Updated: 2023/09/16 22:05:21 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_nb_meal(t_philo *philo)
{
	int	full;

	full = 0;
	pthread_mutex_lock(&philo->data->full->mutex);
		full = philo->data->full->value;
	pthread_mutex_unlock(&philo->data->full->mutex);
	if (full == philo->data->nb_philo)
		return (0);
	return (3);
}

int	is_end(t_philo *philo)
{
	int	is_alive;

	pthread_mutex_lock(&philo->data->check_life->mutex);
	is_alive = philo->data->check_life->value;
	pthread_mutex_unlock(&philo->data->check_life->mutex);
	if (!is_alive || !check_nb_meal(philo))
		return (0);
	else
		return (3);
}

void	ft_usleep(int time, t_philo *philo)
{
	t_ull	time_start;

	time_start = get_time();
	while (1)
	{
		usleep(500);
		if (is_end(philo) <= 1)
			break ;
		if (time_start + time / 1000 <= get_time())
			return ;
	}
}

void	eating(t_philo *philo)
{
	if (!take_fork(philo))
	{
		ft_usleep(philo->data->time_die * 1000, philo);
		return ;
	}
	pthread_mutex_lock(&philo->last_meal->mutex);
	philo->last_meal->value = get_time();
	pthread_mutex_unlock(&philo->last_meal->mutex);
	print("is eating", philo);
	philo->meal_eaten += 1;
	pthread_mutex_lock(&philo->data->full->mutex);
	if (philo->meal_eaten == philo->data->nb_meal)
		philo->data->full->value += 1;
	pthread_mutex_unlock(&philo->data->full->mutex);
	ft_usleep(philo->data->time_eat * 1000, philo);
	release_fork(philo);
}

void	*in_thread(void *thread_info)
{
	t_philo	*philo;

	philo = (t_philo *) thread_info;
	pthread_mutex_lock(philo->data->start);
	pthread_mutex_unlock(philo->data->start);
	if (!(philo->philo_id & 1))
		ft_usleep((philo->data->time_eat - 1000) * 1000, philo);
	else if (philo->philo_id == philo->data->nb_philo)
		ft_usleep(((philo->data->time_eat * 2) - 10) * 1000, philo);
	if (!is_end(philo))
		return (NULL);
	while (1)
	{
		if (is_end(philo) <= 1)
			break ;
		eating(philo);
		if (is_end(philo) <= 1)
			break ;
		print("is sleeping", philo);
		ft_usleep(philo->data->time_sleep * 1000, philo);
		print("is thinking", philo);
		ft_usleep(philo->data->time_think, philo);
	}
	return (NULL);
}
