/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 22:08:30 by madaguen          #+#    #+#             */
/*   Updated: 2023/09/16 22:11:28 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_ull	get_time(void)
{
	t_time	time;
	t_ull	now;

	gettimeofday(&time, NULL);
	now = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (now);
}
