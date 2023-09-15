/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 09:52:49 by mpeulet           #+#    #+#             */
/*   Updated: 2023/09/15 13:28:13 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGES_H
# define MESSAGES_H

# define DEF "\033[0;39m"
# define GREY "\033[0;90m"
# define RED "\033[0;91m"
# define GREEN "\033[0;92m"
# define YELLOW "\033[0;93m"
# define BLUE "\033[0;94m"
# define MAGENTA "\033[0;95m"
# define CYAN "\033[0;96m"
# define WHITE "\033[0;97m"
# define ORANGE "\033[38;5;214m"
# define BLINK_RED "\033[31;5m"

# define ERR_TIME "\033[0;91mError : time_in_ms!\033[0;39m"

# define INIT_EXAMPLE "\033[0;93m\nInstructions : ./philo [Number of philosopher] \
[Time to die (ms)] [Time to eat (ms)] [Time to sleep (ms)] \
(Optional : [Number of lunch per philosopher])\n\n\033[0;39m\
\033[0;92mExample : ./philo 100 300 200 200 25\n\033[0;39m"

# define NB_ARG "\033[0;91mInvalid number or arguments.\033[0;39m"
# define ARG_FORM "\033[0;91mInvalid input : must be positive intagers.\033[0;39m"

# define NB_PHILO "\033[0;91mWARNING!!! : Too many philos! Quit\n\033[0;39m"
# define MS_LOW "\033[0;91mWARNING!!! Do not test time < 60ms\n\033[0;39m"

# define ERR_MALLOC_TID "\033[38;5;214mProgram quit following malloc\
error while allocating data->tid.\033[0;39m"
# define ERR_MALLOC_FORKS "\033[38;5;214mProgram quit following malloc\
error while allocating data->forks.\033[0;39m"
# define ERR_MALLOC_PHILOS "\033[38;5;214mProgram quit following malloc\
error while allocating data->philos.\033[0;39m"

# define STATE_CHANGE "%lu %d %s"
# define DIED "\033[31;5mdied\n\033[0;39m"
# define EATING "\033[0;93mis eating\n\033[0;39m"
# define SLEEPING "\033[0;95mis sleeping\n\033[0;39m"
# define THINKING "\033[0;92mis thinking\n\033[0;39m"
# define FORK_R "\033[0;94mhas taken a fork\n\033[0;39m"
# define FORK_L "\033[0;96mhas taken a fork\n\033[0;39m"

#endif