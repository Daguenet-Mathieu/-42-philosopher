/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                 g                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 22:08:30 by madaguen          #+#    #+#             */
/*   Updated: 2023/09/16 22:11:28 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time_from_start(bool init)
{
	t_time			time;
	static size_t	start_time;
	size_t			now;

	if (init == true)
	{
		gettimeofday(&time, NULL);
		start_time = time.tv_sec * 1000000 + time.tv_usec;
		return (0);
	}
	// printf("srt == %zu\n", start_time);
	gettimeofday(&time, NULL);
	now = time.tv_sec * 1000000 + time.tv_usec;//usec/
	// printf("now == %zu\n", now);
	// printf("s-n == %zu\n", now - start_time);
	return (now - start_time);
}
