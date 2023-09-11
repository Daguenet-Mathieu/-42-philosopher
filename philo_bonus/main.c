/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 20:34:47 by madaguen          #+#    #+#             */
/*   Updated: 2023/06/30 20:34:49 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_sem(t_env *env)
{
	ifsem_open(const char *name, int oflag, 
                mode_t mode, unsigned int value);
}

int	main(int ac, char **av)
{
	t_env	env;
	t_philo	*philo;

	memset(&env, 0, sizeof(t_env));
	if (ac < 5 || ac > 6)
		return (print_error("this program need 4 or 5 arguments\n"));
	if (!check_args(ac, av, &env.init))
		return (1);
	if (!init_sem(&env, &philo))
		return (print_error("fail init sem\n")
			, free(env.last_meal), free(env.fork), 1);
	if (!init_philo(&env, philo))
		return (print_error("fail init fork\n")
			, free(env.last_meal), free(env.fork), 1);
	monitoring(&env, philo);
	destroy_env(&env, philo);
}