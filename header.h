/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   header.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/28 17:22:30 by tblanker      #+#    #+#                 */
/*   Updated: 2022/02/12 13:33:23 by tblanker      ########   odam.nl         */
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
#define EATING 2
#define SLEEPING 3

typedef	struct 		s_philosopher
{
	int				threaded;
	int 			id;
	int				state;
	int				time_since_meal;
}					t_philosopher;


typedef struct 		s_table
{
	int				*fork_list;
	int				n_philosophers;
	int				time_until_starve;
	int				eating_time;
	int				sleeping_time;
	int				number_of_meals;
	t_philosopher	*philo_list;
	pthread_mutex_t	lock;
	struct timeval	time;
	long int		previous_sec;
	int				previous_usec;
	int				timestamp;
}					t_table;


void	put_error(char *error);
void	argument_check(int ac, char **av);
void	initialize(t_table *table, char **av, int ac);
void	start_threading(t_table *table);

# endif