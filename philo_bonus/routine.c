/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 02:52:07 by madaguen          #+#    #+#             */
/*   Updated: 2023/09/17 03:04:14 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

include "philo.h"

void	routine(t_env env, int philo_index)
{
	int	alive;

	alive = 1;
	sem_wait(env.start);
	printf("philo %d attend\n", philo_index);
	sem_post(env.start);
	printf("philo %d est debloque\n", philo_index);
	env.init.start_time = get_time();
	while (alive)
	{
		;
	}
	exit (0);
}
