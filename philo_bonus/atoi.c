/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 06:01:59 by madaguen          #+#    #+#             */
/*   Updated: 2023/04/11 21:54:02 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_space(char c)
{
	if ((c <= 13 && c >= 9) || c == 32)
		return (1);
	return (0);
}

void	ft_skip(char *s, int *i, int *sign)
{
	while (s[*i] && ft_space(s[*i]))
		(*i)++;
	if (s[*i] == '+' || s[*i] == '-')
	{
		if (s[*i] == '-')
			*sign = 1;
		(*i)++;
	}
}

int	ft_isdigit(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_atoi(char *nbr, int *nb)
{
	long	n;
	int		sign;
	int		v;
	int		i;

	sign = 0;
	n = 0;
	v = 1;
	i = 0;
	ft_skip(nbr, &i, &sign);
	if (nbr[i] == 0)
		return (0);
	while (ft_isdigit(nbr[i]) && n <= INT_MAX)
	{
		n = n * 10 + nbr[i] - '0';
		i++;
	}
	if (sign || n > (long)INT_MAX || nbr[i] != 0)
		v = 0;
	*nb = n;
	return (v);
}
