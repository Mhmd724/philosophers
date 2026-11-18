/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharajli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:59:01 by mharajli          #+#    #+#             */
/*   Updated: 2025/04/14 12:59:13 by mharajli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_philosophers.h"

// program must take 5 or 6 arguments (must be integers)
int	check_number_of_arguments(int ac, const char **av)
{
	int	i;
	int	j;

	i = 1;
	if (ac != 5 && ac != 6)
	{
		printf ("Program: ./program number_of_philosophers time_to_die "
			"time_to_eat time_to_sleep [meals_required]\n");
		return (0);
	}
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
			{
				printf ("Invalid input: %s\n", av[i]);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

// the nb of philos maximum 200 and the nb of philosophers must be > 0
int	check_inputs(int ac, const char **av)
{
	int	i;
	int	input;

	i = 1;
	while (i < ac)
	{
		input = ft_atoi(av[i]);
		if (input <= 0)
			return (printf("Invalid input: %d\n", input), 0);
		if (i == 1 && input > 200)
			return (printf("Maximum nb of philosophers 200\n"), 0);
		i++;
	}
	return (1);
}
