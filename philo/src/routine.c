/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:44:43 by mpeulet           #+#    #+#             */
/*   Updated: 2023/09/14 17:58:22 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_state_change(char *s, t_philo *philo)
{
	uint64_t	time;

	time = time_in_ms() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->write);
	if (!strcmp(DIED, s) && !philo->data->dead_philo)
	{
		printf(STATE_CHANGE, time, philo->id, DIED);
		philo->data->dead_philo = 1;
	}
	if (!philo->data->dead_philo)
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

void	*assistant(void	*assistant_void)
{
	t_philo	*assistant;
	
	assistant = (t_philo *)assistant_void;
	while (assistant->data->dead_philo == 0)
	{
		pthread_mutex_lock(&assistant->lock);
		if (time_in_ms() >= assistant->time_left && assistant->eating == 0)
			print_state_change(DIED, assistant);
		if (assistant->data->count_down == 1)
		{
			if (assistant->eat_count == assistant->data->nb_lunch)
					assistant->data->dead_philo = 1; 
		}
		pthread_mutex_unlock(&assistant->lock);
	}
	return ((void *)0);
}

void	*routine(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo *)philo_void;
	philo->time_left = philo->data->ttd + time_in_ms();
	pthread_create(&philo->philo_tid, NULL, &assistant, (void *)philo);
	while (philo->data->dead_philo == 0)
	{
		lunch_time(philo);
		print_state_change(THINKING, philo);
	}
	pthread_join(philo->philo_tid, NULL);
	return ((void *)0);
}

void	multi_threading(t_data *data)
{
	int			i;

	i = -1;
	data->start_time = time_in_ms();
	while (++i < (int)data->nb_philo)
		pthread_create(&data->tid[i], NULL, &routine, &data->philos[i]);
	i = -1;
	while (++i < (int)data->nb_philo)
		pthread_join(data->tid[i], NULL);
}