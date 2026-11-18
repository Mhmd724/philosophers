/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharajli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:34:31 by mharajli          #+#    #+#             */
/*   Updated: 2025/04/14 12:34:32 by mharajli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_philosophers.h"

int	ft_atoi(const char *av)
{
	int		sign;
	long	value;

	value = 0;
	sign = 1;
	while (*av == ' ' || (*av >= '\t' && *av <= '\r'))
		av++;
	if (*av == '+' || *av == '-')
	{
		if (*av == '-')
			sign = -1;
		av++;
	}
	while (*av >= '0' && *av <= '9')
	{
		value = (value * 10) + (*av - '0');
		if (sign == 1 && value > INT_MAX)
			return (-1);
		if (sign == -1 && value < INT_MIN)
			return (-1);
		av++;
	}
	return ((int)(sign * value));
}

// gets the current timestamp in milliseconds
long int	get_timestamp(void)
{
	struct timeval	time_now;

	gettimeofday(&time_now, NULL);
	return ((time_now.tv_sec * 1000) + (time_now.tv_usec / 1000));
}

// passes the time in milliseconds to the simulation
// this function is used to simulate the time taken for a philosopher to eat or sleep
void	time_to_pass(long int time_in_ms, t_simulation *simulation)
{
	long int	start_time;

	start_time = get_timestamp();
	while (get_timestamp() - start_time < time_in_ms)
	{
		if (has_philosopher_died(simulation))
			break ;
		if (has_simulation_ended(simulation))
			break ;
		usleep(100);
	}
}
