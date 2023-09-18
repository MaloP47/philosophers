/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:44:43 by mpeulet           #+#    #+#             */
/*   Updated: 2023/09/18 13:33:26 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	lunch_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->forks[0]]);
	define_printing(philo, 0, FORK_R);
	pthread_mutex_lock(&philo->data->forks[philo->forks[1]]);
	define_printing(philo, 0, FORK_L);
	define_printing(philo, 0, EATING);
	pthread_mutex_lock(&philo->lock);
	philo->time_left = time_in_ms();
	pthread_mutex_unlock(&philo->lock);
	break_time(philo->data, philo->data->tte);
	if (!monitoring_table(philo->data))
	{
		pthread_mutex_lock(&philo->lock);
		philo->eat_count++;
		pthread_mutex_unlock(&philo->lock);
	}
	define_printing(philo, 0, SLEEPING);
	pthread_mutex_unlock(&philo->data->forks[philo->forks[1]]);
	pthread_mutex_unlock(&philo->data->forks[philo->forks[0]]);
	break_time(philo->data, philo->data->tts);
}

void	waiting_time(t_philo *philo, int mute)
{
	uint64_t	ttt;

	pthread_mutex_lock(&philo->lock);
	ttt = (philo->data->ttd - (time_in_ms() - philo->time_left)
	- philo->data->tte) / 2;
	pthread_mutex_unlock(&philo->lock);
	if (!ttt && mute)
		ttt = 1;
	if (ttt > 600)
		ttt = 200;
	if (!mute)
		define_printing(philo, 0, THINKING);
	break_time(philo->data, ttt);
}

void	*case_one(t_philo *philo)
{
	define_printing(philo, 0, FORK_R);
	ft_usleep(philo->data->ttd);
	define_printing(philo, 0, DIED);
	return (0);
}

void	*routine(void *philo_void)
{
	t_philo *philo;

	philo = (t_philo *)philo_void;
	pthread_mutex_lock(&philo->lock);
	philo->time_left = philo->data->start_time;
	pthread_mutex_unlock(&philo->lock);
	if (!philo->data->ttd)
		return (0);
	if (philo->data->nb_philo == 1)
		return (case_one(philo));
	else if (philo->id % 2)
		waiting_time(philo, 1);
	while (!monitoring_table(philo->data))
	{
		lunch_time(philo);
		waiting_time(philo, 0);
	}
	return (0);
}
