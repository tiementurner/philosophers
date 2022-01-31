/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   header.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/28 17:22:30 by tblanker      #+#    #+#                 */
/*   Updated: 2022/01/31 17:13:33 by tblanker      ########   odam.nl         */
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

typedef struct s_table
{
	int		n_forks;
	int		n_philosophers;
	int		time_until_starve;
	int		eating_time;
	int		sleeping_time;
	int		number_of_meals;
}				t_table;


void	put_error(char *error);

# endif