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

typedef struct timeval		t_time;
typedef unsigned long long	t_ull;

typedef struct s_mutex
{
	t_ull			value;
	pthread_mutex_t	mutex;

}					t_mutex;

typedef struct s_init
{
	t_ull		start_time;
	t_mutex		*check_life;
	t_mutex		*full;
	int			nb_meal;
	int			nb_philo;
	int			time_die;
	int			time_eat;
	int			time_sleep;
}				t_init;

typedef struct s_env
{
	t_init			init;
	t_mutex			check_life;
	t_mutex			full;
	t_mutex			*last_meal;
	pthread_mutex_t	*fork;
}					t_env;

typedef struct s_philo
{
	t_init			*data;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	t_mutex			*last_meal;
	int				meal_eaten;
	int				philo_id;
	pthread_t		thread_id;
}					t_philo;

void	eating(t_philo *philo);
int		check_nb_meal(t_philo *philo);;
void	*in_thread(void *thread_info);
int		ft_strcmp(char *s, char *s1);
int		print_error(char *s);
void	print(char *s, t_philo *philo);
void	take_mutex(void *mutex, char *s, t_philo *philo);
void	release_mutex(void *mutex);
int		take_fork(t_philo *philo);
void	release_fork(t_philo *philo);
int		check_death(t_philo *philo, t_init init, int *index);
void	monitoring(t_env *env, t_philo *philo);
int		verif_arg(char *s, int *nb);
int		check_args(int ac, char **av, t_init *init);
int		init_mutex(t_env *env, t_philo **philo);
void	init_struct_philo(t_env *env, t_philo *philo, int i);
int		init_philo(t_env *env, t_philo *philo);
void	join_thread(t_init init, t_philo *philo);
void	destroy_mutex(t_env *env);
void	destroy_env(t_env *env, t_philo *philo);
int		ft_space(char c);
void	ft_skip(char *s, int *i, int *sign);
int		ft_isdigit(char c);
int		ft_atoi(char *nbr, int *nb);
t_ull	get_time(void);

#endif
