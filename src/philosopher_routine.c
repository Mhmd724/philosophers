/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharajli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:07:15 by mharajli          #+#    #+#             */
/*   Updated: 2025/04/14 12:07:16 by mharajli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_philosophers.h"

void	*single_philosopher(void *philosopher) // if one philosopher has entered this function act like (take a fork then die after waiting)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)philosopher;
	action_log(philo, "has taken a fork");
	usleep(philo->simulation->time_to_die * 1000);
	action_log(philo, "died");
	return (NULL);
}

void	*multiple_philosophers(void *philo) // for more than one fork
{
	t_philosopher	*philosopher;
	int				time_to_sleep;

	philosopher = (t_philosopher *)philo;
	time_to_sleep = philosopher->simulation->time_to_sleep;
	if (philosopher->id % 2 == 0) // if the philosopher id is even, wait half of time_to_eat so odd ones take forks first
		time_to_pass(philosopher->simulation->time_to_eat / 2,
			philosopher->simulation);
	while (!has_philosopher_died(philosopher->simulation)) // loop until a philosopher dies (eat, sleep, thinks)
	{
		eat(philosopher);
		if (has_simulation_ended(philosopher->simulation))
			break ;
		action_log(philosopher, "is sleeping");
		time_to_pass(time_to_sleep, philosopher->simulation); // to pass the time of sleeping
		action_log(philosopher, "is thinking");
	}
	return (NULL);
}
