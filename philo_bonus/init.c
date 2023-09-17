/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 20:18:10 by madaguen          #+#    #+#             */
/*   Updated: 2023/09/17 03:05:51 by madaguen         ###   ########.fr       */
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

int	init_philo(t_env *env)
{
	int	i;
	int	pid;
	
	i = 0;
	while (i < env->init.nb_philo)
	{
		pid = fork();
		if (pid == 0)
			routine(*env, i + 1);
		if (pid == -1)
			return (printf("fail to create philo %d\n", i), 0);
		//env->pid[i] = pid;
		i++;
	}
	return (1);
}
