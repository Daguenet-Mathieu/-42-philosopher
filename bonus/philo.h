/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 04:59:27 by madaguen          #+#    #+#             */
/*   Updated: 2023/07/01 04:59:53 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

typedef struct timeval		t_time;
typedef unsigned long long	t_ull;

typedef struct s_init
{
	int		nb_meal;
	int		nb_philo;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	t_ull	start_time;

}				t_init;

typedef struct s_env
{
	sem_t	*check_life;
	sem_t	*forks;
	sem_t	*full;
}		t_env;

typedef struct s_philo
{
	int		philo_id;
	int		philo_pid;
	int		meal_eaten;
	t_init	data;
}			t_philo;

t_ull   get_time();

#endif
