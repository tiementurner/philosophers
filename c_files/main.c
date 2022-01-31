/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/28 17:22:18 by tblanker      #+#    #+#                 */
/*   Updated: 2022/01/31 17:32:18 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*print_hallo(void *var)
{
	t_table *table;

	table = var;
	if (table->n_forks == 0)
		printf("forks are gone!");
	return (0);
}

int main(int ac, char **av)
{
	pthread_t	t1, t2;
	t_table		table;
	int			forks[ft_atoi(av[1])];
	int			i;

	table.n_philosophers = ft_atoi(av[1]);
	i = 0;
	while (i < table.n_philosophers)
	{
		forks[i] = 1;
		i++;
	}
	printf("%d\n", forks[0]);

	table.n_forks = 10;
	pthread_create(&t1, NULL, print_hallo, &table);
	pthread_create(&t2, NULL, print_hallo, &table);

	pthread_join(t1, NULL);
	while (table.n_forks > 0)
		table.n_forks--;
	pthread_join(t2, NULL);
	return (0);
}
