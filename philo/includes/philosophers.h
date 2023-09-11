/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:03:58 by mpeulet           #+#    #+#             */
/*   Updated: 2023/09/11 15:30:51 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <strings.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdint.h>
# include <limits.h>

# include "messages.h"

typedef struct s_data	t_data;

typedef struct s_philo
{
	pthread_t		pid;
	unsigned int	id;
	unsigned int	eat_count;

	t_data			*data;
}		t_philo;

typedef struct s_data
{
	uint64_t		start_time;
	unsigned int	nb_philo;
	uint64_t		ttd;
	uint64_t		tte;
	uint64_t		tts;
	unsigned int	nb_lunch;
	pthread_t		monitor;
}		t_data;

/* *** init.c *** */

int			struct_init(t_data *data);

/* *** parsing.c *** */

int			ft_str_is_digit(char *s);
long		ft_atol(const char *str);
void		warning_limits(t_data *data);
int			check_args(int ac, char **av, t_data *main);

/* *** utils.c *** */

size_t		ft_strlen(const char *s);
void		putstr_errendl(char *s);
int			error_exit(char *s);
uint64_t	time_in_ms(void);
int			ft_usleep(__useconds_t microsec);

#endif