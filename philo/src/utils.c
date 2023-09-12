/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 10:08:27 by mpeulet           #+#    #+#             */
/*   Updated: 2023/09/12 16:31:16 by mpeulet          ###   ########.fr       */
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

void	free_all(t_data *data)
{
	if (data->tid)
		free(data->tid);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}

void	destroy_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < (int)data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].lock);
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->lock);
}

void	putstr_errendl(char *s)
{
	if (!s)
		return ;
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
}

int	clean_exit(char *s, t_data *data)
{
	putstr_errendl(s);
	if (data)
		destroy_mutex(data);
	free_all(data);
	return (1);
}

uint64_t	time_in_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, 0))
		putstr_errendl(ERR_TIME);
	return (((uint64_t)tv.tv_sec * 1000) + ((uint64_t)tv.tv_usec / 1000));
}

int	ft_usleep(__useconds_t microsec)
{
	uint64_t	time_ms;

	time_ms = time_in_ms();
	while (time_in_ms() - time_ms < microsec)
		usleep(microsec / 10);
	return (1);
}
