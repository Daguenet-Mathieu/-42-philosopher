/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 20:19:02 by madaguen          #+#    #+#             */
/*   Updated: 2023/06/30 20:19:49 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strcmp(char *s, char *s1)
{
	int	i;

	i = 0;
	if (!s || !s1)
		return (0);
	while (s[i] && s[i] == s1[i])
		i++;
	if (s[i] == 0 && s1[i] == 0)
		return (1);
	return (0);
}

int	print_error(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	write(2, s, i);
	return (0);
}

void	print(char *s, t_philo *philo)
{
	t_ull	now;
	int		is_alive;
	t_ull	start_time;

	start_time = philo->data->start_time;
	pthread_mutex_lock(&philo->data->check_life->mutex);
	is_alive = philo->data->check_life->value;
	if (is_alive >= 2 || (is_alive <= 1) && ft_strcmp(s, "died"))
	{
		now = get_time();
		printf("%llu %d %s\n", now - start_time, philo->philo_id, s);
	}
	pthread_mutex_unlock(&philo->data->check_life->mutex);
}
