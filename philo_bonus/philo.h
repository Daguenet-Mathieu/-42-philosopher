/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 04:59:27 by madaguen          #+#    #+#             */
/*   Updated: 2023/09/17 03:06:58 by madaguen         ###   ########.fr       */
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
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>

typedef struct timeval		t_time;
typedef unsigned long long	t_ull;

typedef struct s_init
{
	int		nb_meal;
	int		nb_philo;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	t_ull	start_time;// a initialiser dans le thread ou dans le parent dans le futur et la simulation ne demarre que quand ce temps est atteint?

}		t_init;

typedef struct s_env
{
	sem_t	check_life;
	sem_t	forks;
	sem_t	full;
	sem_t	start;
	int	*philo_pid;
	t_init	init;
}		t_env;

t_ull   get_time();
void	routine(t_env env, philo_index);
int	verif_arg(char *s, int *nb);
int	check_args(int ac, char **av, t_init *init);
int	init_philo(t_env *env);
int	init_sem(char *name, int value);

#endif
