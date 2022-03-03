/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   header.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/28 17:22:30 by tblanker      #+#    #+#                 */
/*   Updated: 2022/03/03 13:13:38 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include "libft/libft.h"

#define NOTHING 0
#define THINKING 1
#define SLEEPING 3
#define DEAD 4

#define TAKEN 0
#define ON_TABLE 1

typedef	struct 		s_philosopher
{
	int				threaded;
	int 			id;
	int				state;
	int				time_since_meal;
	int				forks_in_hand;
	int				left;
	int				right;
	int				start;
	int				meals;
}					t_philosopher;


typedef struct 		s_table
{
	int				finished_eating;
	int				funeral;
	int				*fork_list;
	int				n_philosophers;
	int				time_until_starve;
	int				eating_time;
	int				sleeping_time;
	int				number_of_meals;
	t_philosopher	*philo_list;
	pthread_mutex_t	*lock;
	struct timeval	time;
	unsigned int	previous_sec;
	long	int		previous_usec;
	int				timestamp;
	pthread_mutex_t	sync_lock;
}					t_table;


void	put_error(char *error);
void	argument_check(int ac, char **av);
void	initialize(t_table *table, char **av, int ac);
void	start_threading(t_table *table);
void	try_to_eat(t_table *table, t_philosopher *philo);
void	sleep_and_think(t_table *table, t_philosopher *philo);
void	*check_pulse_rates(void *arg);
void	check_stomach(t_table *table, t_philosopher *philo);
void	get_timestamp(t_table *table);

# endif