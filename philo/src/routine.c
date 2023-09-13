/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:44:43 by mpeulet           #+#    #+#             */
/*   Updated: 2023/09/13 16:07:05 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_state_change(char *s, t_philo *philo)
{
	uint64_t	time;

	time = time_in_ms - philo->data->start_time;
	pthread_mutex_lock(&philo->data->write);
	printf(STATE_CHANGE, time, philo->id, s);
	pthread_mutex_unlock(&philo->data->write);
}

void	lock_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_state_change(FORK_R, philo);
	pthread_mutex_lock(philo->left_fork);
	print_state_change(FORK_L, philo);
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	print_state_change(SLEEPING, philo);
	ft_usleep(philo->data->tts);
}

void	lunch_time(t_philo *philo)
{
	lock_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->eat_count = 1;
	philo->time_left = time_in_ms() + philo->data->ttd;
	print_state_change(EATING, philo);
	philo->eat_count++;
	ft_usleep(philo->data->tte);
	philo->eat_count = 1;
	pthread_mutex_unlock(&philo->lock);
	unlock_forks(philo);
}

void	assistant(void	*assistant_void)
{
	t_philo	*assistant;
	assistant = (t_philo *)assistant_void;
	While (assistant->data->dead_philo == 0)
	{
		pthread_mutex_lock(&assistant->lock);
		if (time_in_ms() >= assistant->time_left && assistant->eating == 0)
			print_state_change(DIED, assistant);
	} 
}

void	*routine(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo *)philo_void;
	philo->time_left = philo->data->ttd + time_in_ms;
	
}