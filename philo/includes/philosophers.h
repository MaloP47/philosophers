/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:03:58 by mpeulet           #+#    #+#             */
/*   Updated: 2023/09/21 14:36:22 by mpeulet          ###   ########.fr       */
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
# include <string.h>

# include "messages.h"

typedef struct s_data	t_data;

typedef struct s_philo
{
	t_data			*data;

	pthread_t		philo_tid;

	unsigned int	id;
	unsigned int	eat_count;

	uint64_t		last_meal;

	pthread_mutex_t	lunch_time;
	pthread_mutex_t	fork_left;
	pthread_mutex_t	*fork_right;
}		t_philo;

typedef struct s_data
{
	t_philo			*philo;

	int				philo_has_finish_eating;
	unsigned int	nb_lunch;
	int				nb_philo;
	unsigned int	dead_philo;

	uint64_t		eating;

	uint64_t		start_time;
	uint64_t		ttd;
	uint64_t		tte;
	uint64_t		tts;

	pthread_mutex_t	one_dead;
	pthread_mutex_t	write;
	pthread_mutex_t	nb_of_lunch_reached;

}		t_data;

/* *** clean_exit.c *** */

void		destroy_mutex(t_data *data);
void		putstr_errendl(char *s);
int			clean_exit(char *s, t_data *data);

/* *** parsing_printing.c *** */

int			check_args(int ac, char **av, t_data *data);
void		warning_limits(t_data *data);
int			struct_init(int ac, char **av, t_data *data);
void		print_state_change(char *s, t_philo *philo);
void		define_printing(t_data *data, t_philo *philo, char *action);

/* *** philosophers.c *** */

int			init_philo(t_data *data);
int			init_data(t_data *data);
int			monitoring(t_data *data);
int			threading(t_data *data);
int			philosopher(t_data *data);

/* *** philosophers_bis.c *** */

int			init_philo_util(t_data *data);
void		monitoring_util_lock_lunch(t_data *data, int i);

/* *** routine.c *** */

int			philo_died(t_data *data);
int			grab_forks(t_data *data, t_philo *philo);
int			lunch_time(t_data *data, t_philo *philo);
void		nap_time(t_data *data, t_philo *philo);
void		*routine(void *philo_pointer);

/* *** utils.c *** */

size_t		ft_strlen(const char *s);
int			ft_str_is_digit(char *s);
long		ft_atol(char *str);
uint64_t	time_in_ms(void);
int			ft_usleep(t_data *data, __useconds_t microsec);

#endif