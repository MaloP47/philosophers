/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 20:08:33 by mpeulet           #+#    #+#             */
/*   Updated: 2023/08/15 21:41:07 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	struct_init(t_philo *philo)
{
	philo->nb_philo = 0;
	philo->ttd = 0;
	philo->tte = 0;
	philo->tts = 0;
	philo->nb_lunch = -1;
	return (1);
}
