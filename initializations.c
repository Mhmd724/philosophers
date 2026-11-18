/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharajli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:56:50 by mharajli          #+#    #+#             */
/*   Updated: 2025/04/14 11:56:51 by mharajli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_philosophers.h"

// initialize all the mutexes and forks(array) needed for the simulation
int	init_mutexes(t_simulation *simulation)
{
	int	i;

	i = 0;
	simulation->forks = malloc(sizeof(t_fork) * simulation->nbs_philosophers);
	if (!simulation->forks)
		return (printf("Fork memory allocation Failed.\n"), 0);
	while (i < simulation->nbs_philosophers)
	{
		if (pthread_mutex_init(&simulation->forks[i].fork_mutex, NULL))
			return (printf("Fork mutex initialization failed.\n"), 0);
		simulation->forks[i].philo_taken_by = 0;
		i++;
	}
	if (pthread_mutex_init(&simulation->print, NULL))
		return (printf("Print mutex initialization failed.\n"), 0);
	if (pthread_mutex_init(&simulation->is_eating, NULL))
		return (printf("Eat mutex initialization failed.\n"), 0);
	if (pthread_mutex_init(&simulation->has_eaten, NULL))
		return (printf("Has eaten mutex initialization failed.\n"), 0);
	if (pthread_mutex_init(&simulation->monitor_end, NULL))
		return (printf("Monitor end mutex initialization failed.\n"), 0);
	if (pthread_mutex_init(&simulation->monitor_die, NULL))
		return (printf("Monitor die mutex initialization failed.\n"), 0);
	return (1);
}

// initialize the philosophers(array) needed for the simulation and its attributes
// (id, left_fork, right_fork, time_last_meal, eat_count, simulation)
int	init_philosophers(t_simulation *simulation)
{
	int	i;
	int	nb_philo;

	i = 0;
	nb_philo = simulation->nbs_philosophers;
	simulation->philosophers = malloc(sizeof(t_philosopher) * nb_philo);
	if (!simulation->philosophers)
		return (printf("Philosopher memory allocation Failed.\n"), 0);
	while (i < simulation->nbs_philosophers)
	{
		simulation->philosophers[i].id = i + 1;
		simulation->philosophers[i].right_fork = i;
		simulation->philosophers[i].left_fork = (i + 1) % nb_philo;
		simulation->philosophers[i].time_last_meal = 0;
		simulation->philosophers[i].eat_count = 0;
		simulation->philosophers[i].simulation = simulation;
		i++;
	}
	return (1);
}

// destroy all the mutexes, frees forks(array) and philosophers(array) used in the simulation
void	destroy_mutexes(t_simulation *simulation)
{
	int	i;

	i = 0;
	while (i < simulation->nbs_philosophers)
	{
		pthread_mutex_destroy(&simulation->forks[i].fork_mutex);
		i++;
	}
	pthread_mutex_destroy(&simulation->print);
	pthread_mutex_destroy(&simulation->is_eating);
	pthread_mutex_destroy(&simulation->has_eaten);
	pthread_mutex_destroy(&simulation->monitor_end);
	pthread_mutex_destroy(&simulation->monitor_die);
	free(simulation->philosophers);
	free(simulation->forks);
}
