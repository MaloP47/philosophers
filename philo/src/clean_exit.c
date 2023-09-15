/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 14:04:09 by mpeulet           #+#    #+#             */
/*   Updated: 2023/09/15 14:05:23 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
