/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/05 19:21:28 by tblanker      #+#    #+#                 */
/*   Updated: 2022/02/12 02:07:09 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// void	philo_thread(t_table *table)
// {
// 	int id;
// 	int fork_left;
// 	int	fork_right;

// 	id = 0;
// 	while (table->philo_list[id].threaded)
// 		id++;
// 	if (id == 0)
// 		fork_left = table->n_philosophers;
// 	else
// 		fork_left = id - 1;
// 	if(id == table->n_philosophers - 1)
// 		fork_right = 0;
// 	else
// 		fork_right = id + 1;
// 	if (table->fork_list[fork_left] && table->fork_list[fork_right])
// 		table->philo_list[id].state = EATING;
// }

static	int	synchronize_threads(t_table *table)
{
	int	id;


	id = 0;
	while (table->philo_list[id].threaded)
		id++;
	table->philo_list[id].threaded = 1;
	while (table->philo_list[0].threaded == 0);//
	return (id);
}

void	get_timestamp(t_table *table)
{
	gettimeofday(&table->time, NULL);
	table->timestamp += (table->time.tv_sec - table->previous_sec) * 1000 +
						(table->time.tv_usec / 1000 - table->previous_usec / 1000);
	table->previous_sec = table->time.tv_sec;
	table->previous_usec = table->time.tv_usec;
}

void	try_to_eat(t_table *table, t_philosopher *philo)
{
	int left_fork;
	int	right_fork;

	if (table->n_philosophers == 1)
		return ;
	left_fork = philo->id;
	right_fork = philo->id - 1;
	if (philo->id == 0)
		right_fork = table->n_philosophers - 1;
	if (philo->id == table->n_philosophers - 1)
		right_fork = 0;
	printf("value: id: %d----left: %d, right:%d\n", philo->id, table->fork_list[left_fork], table->fork_list[right_fork]);
//	printf("id: id: %d----left: %d, right:%d\n", philo->id, left_fork, right_fork);
	pthread_mutex_lock(&table->lock);
	if (table->fork_list[left_fork] && table->fork_list[right_fork])
	{
		table->fork_list[left_fork] = 0;
		table->fork_list[right_fork] = 0;
		pthread_mutex_unlock(&table->lock);
		printf("%d %d Has taken a fork.\n", table->timestamp, philo->id + 1);
		printf("%d %d is eating\n", table->timestamp, philo->id + 1);
		usleep(table->eating_time * 1000);
	//	pthread_mutex_lock(&table->lock);
		table->fork_list[left_fork] = 1;
		table->fork_list[right_fork] = 1;
	//	pthread_mutex_unlock(&table->lock);
	}
}

void *test_thread(void *arg)
{
	t_table 		*table;
	t_philosopher 	*philo;
	int				id;
	int				printed;

	printed = 0;
	table = (t_table *) arg;
	id = synchronize_threads(table);
	philo = &table->philo_list[id];
	while(1)
	{
		philo->time_since_meal += table->timestamp;
		try_to_eat(table, philo);
		// if (time_since_meal > philo->time_to_die)
		// 	printf("guy is dead");
	}
	return (0);
}



void	start_threading(t_table *table)
{
	pthread_t		thread_list[table->n_philosophers];
	int				i;

	pthread_mutex_init(&table->lock, NULL);
	i = 0;
	while (i < table->n_philosophers)
	{
		pthread_create(&thread_list[i], NULL, test_thread, table);
		i++;
	}
	while (table->philo_list[0].threaded == 0)
	table->timestamp = 0;
	gettimeofday(&table->time, NULL);
	table->previous_sec = table->time.tv_sec;
	table->previous_usec = table->time.tv_usec;
	while (1)
	{
		get_timestamp(table);
	}
	i = 0;
	while (i < table->n_philosophers)
	{
		pthread_join(thread_list[i], NULL);
		i++;
	}
}
