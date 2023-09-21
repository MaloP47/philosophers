/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 13:08:13 by mpeulet           #+#    #+#             */
/*   Updated: 2023/09/21 13:09:42 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	ft_str_is_digit(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!(s[i] >= 48 && s[i] <= 57))
			return (0);
		i++;
	}
	return (1);
}

long	ft_atol(char *str)
{
	int		i;
	int		sign;
	long	nb;

	if (!str)
		return (0);
	i = 0;
	nb = 0;
	sign = 1;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32)))
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i++] == 45)
			sign *= -1;
	}
	while (str[i] && (str[i] >= 48 && str[i] <= 57))
	{
		nb = (nb * 10) + (str[i] - 48);
		if (nb * sign > INT_MAX || nb * sign < INT_MIN)
			return (-2147483649);
		i++;
	}
	return (nb * sign);
}

uint64_t	time_in_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, 0))
		putstr_errendl(ERR_TIME);
	return (((uint64_t)tv.tv_sec * 1000) + ((uint64_t)tv.tv_usec / 1000));
}

int	ft_usleep(t_data *data, __useconds_t microsec)
{
	uint64_t	time_ms;

	time_ms = time_in_ms();
	while (time_in_ms() - time_ms < microsec)
	{
		pthread_mutex_lock(&data->one_dead);
		if (data->dead_philo)
		{
			pthread_mutex_unlock(&data->one_dead);
			return (0);
		}
		pthread_mutex_unlock(&data->one_dead);
		usleep(10);
	}
	return (1);
}
