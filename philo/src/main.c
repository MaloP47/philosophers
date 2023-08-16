/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:05:27 by mpeulet           #+#    #+#             */
/*   Updated: 2023/08/15 21:52:14 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_philo	philo;

	if (!check_args(ac, av, &philo))
		return (EXIT_FAILURE);
	printf("Philo:[%d]\nttd:[%d]\ntte:[%d]\ntts:[%d]\nlunch:[%d]\n", philo.nb_philo, philo.ttd, philo.tte, philo.tts, philo.nb_lunch);
	return (EXIT_SUCCESS);
}
