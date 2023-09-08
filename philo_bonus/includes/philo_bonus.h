/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:03:58 by mpeulet           #+#    #+#             */
/*   Updated: 2023/09/08 14:00:24 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <strings.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdint.h>
# include <limits.h>

# include "messages_bonus.h"

typedef struct s_philo
{
	int	nb_philo;
	int	ttd;
	int	tte;
	int	tts;
	int	nb_lunch;
}		t_philo;

/* *** init_bonus.c *** */

int			struct_init(t_philo *philo);

/* *** parsing_bonus.c *** */

int			ft_str_is_digit(char *s);
long		ft_atol(const char *str);
void		warning_limits(t_philo *philo);
int			check_args(int ac, char **av, t_philo *philo);

/* *** utils_bonus.c *** */

size_t		ft_strlen(const char *s);
void		putstr_errendl(char *s);
int			error_exit(char *s);
uint64_t	time_in_ms(void);
int			ft_usleep(__useconds_t microsec);

#endif