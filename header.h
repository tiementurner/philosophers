/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   header.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/28 17:22:30 by tblanker      #+#    #+#                 */
/*   Updated: 2022/03/10 18:41:54 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#	ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>

# define ALIVE 0
# define DEAD 1

typedef struct s_philosopher
{
	int				threaded;
	int				id;
	int				state;
	int				time_since_meal;
	int				forks_in_hand;
	int				left;
	int				right;
	int				start;
	int				meals;
}					t_philosopher;

typedef struct s_table
{
	int				finished_eating;
	int				funeral;
	int				n_philosophers;
	int				time_until_starve;
	int				eating_time;
	int				sleeping_time;
	int				number_of_meals;
	t_philosopher	*philo_list;
	pthread_mutex_t	*lock;
	struct timeval	time;
	unsigned int	start_sec;
	long int		start_usec;
	int				timestamp;
	pthread_mutex_t	sync_lock;
	pthread_mutex_t	check_lock;
	pthread_mutex_t	print_lock;
	pthread_t		*thread_list;
}					t_table;

int		check_if_done(t_table *table, t_philosopher *philo);
void	put_error(char *error, int usage);
int		validate_input(t_table *table, int ac, char **av);
int		initialize(t_table *table);
void	start_threading(t_table *table);
void	eat(t_table *table, t_philosopher *philo);
void	sleep_and_think(t_table *table, t_philosopher *philo);
void	*check_pulse_rates(void *arg);
void	check_stomach(t_table *table, t_philosopher *philo);
int		get_timestamp(t_table *table);
void	philo_print(char *message, t_table *table, t_philosopher *philo);
int		get_philo_id(t_table *table);
int		ft_atoi(const char *str);
int		ft_strlen(const char *s);
void	free_machine(t_table *table);

#	endif