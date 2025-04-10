#include "philo.h"

static int	skip_white_space(char const *const str, int i)
{
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
	{
		i++;
	}
	return (i);
}

static void	sign_op(bool sign, unsigned int tmp_res, int *const res)
{
	if (sign == true)
	{
		*res = (int)(tmp_res * -1);
	}
	else
	{
		*res = tmp_res;
	}
}

static int	check_overflow(unsigned int tmp_res, bool sign)
{
	unsigned int const	min_int = (unsigned int)INT_MAX + 1;

	if ((tmp_res > INT_MAX && !sign) || (tmp_res > min_int && sign))
		return (false);
	return (true);
}

bool	ft_atoi(char const *const str, int *const res)
{
	int				i;
	unsigned int	tmp_res;
	bool			sign;

	tmp_res = 0;
	sign = false;
	i = skip_white_space(str, 0);
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = true;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		if ((tmp_res * 10 + (str[i] - '0')) / 10 != tmp_res)
			return (false);
		tmp_res = tmp_res * 10 + (str[i] - '0');
		i++;
	}
	if (check_overflow(tmp_res, sign) == false || str[i] != 0)
		return (false);
	sign_op(sign, tmp_res, res);
	return (true);
}
