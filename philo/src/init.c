/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 20:08:33 by mpeulet           #+#    #+#             */
/*   Updated: 2023/09/11 15:07:10 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	struct_init(t_data *data)
{
	data->nb_philo = 0;
	data->ttd = 0;
	data->tte = 0;
	data->tts = 0;
	data->nb_lunch = -1;
	return (1);
}
