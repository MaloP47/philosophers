/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:05:27 by mpeulet           #+#    #+#             */
/*   Updated: 2023/09/11 15:24:23 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 1)
		return (error_exit(INIT_EXAMPLE));
	if (!check_args(ac, av, &data))
		return (EXIT_FAILURE);
	data.start_time = time_in_ms();
	printf("Started at : [%lu]\n\nPhilo:[%u]\nttd:[%lu]\ntte:[%lu]\ntts:[%lu]\nlunch:[%u]\n", data.start_time, data.nb_philo, data.ttd, data.tte, data.tts, data.nb_lunch);
	return (EXIT_SUCCESS);
}
