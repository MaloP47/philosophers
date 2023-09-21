/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 13:10:45 by mpeulet           #+#    #+#             */
/*   Updated: 2023/09/21 13:11:29 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < (int)data->nb_philo)
	{
		pthread_mutex_destroy(&data->philo[i].fork_left);
		pthread_mutex_destroy(&data->philo[i].lunch_time);
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->one_dead);
	pthread_mutex_destroy(&data->nb_of_lunch_reached);
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
	if (data->philo)
		free(data->philo);
	return (1);
}
