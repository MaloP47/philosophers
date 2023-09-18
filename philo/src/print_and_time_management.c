/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_and_time_management.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:30:06 by mpeulet           #+#    #+#             */
/*   Updated: 2023/09/18 13:30:11 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_state_change(char *s, t_philo *philo)
{
	uint64_t	time;

	time = time_in_ms() - philo->data->start_time;
	printf(STATE_CHANGE, time, philo->id, s);
}

void	define_printing(t_philo *philo, int	dead, char *action)
{
	pthread_mutex_lock(&philo->data->write);
	if (monitoring_table(philo->data) && !dead)
	{
		pthread_mutex_unlock(&philo->data->write);
		return ;
	}
	print_state_change(action, philo);
	pthread_mutex_unlock(&philo->data->write);
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

void	break_time(t_data *data, uint64_t action_time)
{
	uint64_t	break_time;

	break_time = time_in_ms() + action_time;
	while (time_in_ms() < break_time)
	{
		if (monitoring_table(data))
			break ;
		ft_usleep(100);
	}
}
