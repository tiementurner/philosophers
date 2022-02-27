/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   death_checks.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/25 17:50:28 by tblanker      #+#    #+#                 */
/*   Updated: 2022/02/27 20:17:56 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void		*check_pulse_rates(void *arg)
{
	int i;
	t_table	*table;

	table = (t_table *) arg;
	i = 0;
	while (!table->funeral)
	{
		i = 0;
		while (i < table->n_philosophers)
		{
			if (table->philo_list[i].state == DEAD || table->finished_eating == table->n_philosophers)
			{
				get_timestamp(table);
				printf("ending millisecond: %d\n", table->timestamp);
				table->funeral = 1;
				break ;
			}
			i++;
		}
		usleep(50);
	}
	return (0);
}

void		check_stomach(t_table *table, t_philosopher *philo)
{
	if (table->timestamp - philo->time_since_meal > table->time_until_starve)
	{
		printf("%d %d died.\n", table->timestamp, philo->id + 1);
		philo->state = DEAD;
	}
}
