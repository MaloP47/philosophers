/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:05:27 by mpeulet           #+#    #+#             */
/*   Updated: 2023/09/12 16:05:59 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 1)
		return (putstr_errendl(INIT_EXAMPLE), 0);
	if (!check_args(ac, av, &data))
		return (clean_exit(NULL, &data));
	data.start_time = time_in_ms();
	printf("Started at : [%lu]\n\nPhilo:[%u]\nttd:[%lu]\ntte:[%lu]\ntts:[%lu]\nlunch:[%u]\n", data.start_time, data.nb_philo, data.ttd, data.tte, data.tts, data.nb_lunch);
	clean_exit(NULL, &data);
	return (EXIT_SUCCESS);
}
