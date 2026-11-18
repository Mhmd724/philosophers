/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharajli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:06:01 by mharajli          #+#    #+#             */
/*   Updated: 2025/04/14 12:06:03 by mharajli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_philosophers.h"

// start the simulation by creating the threads for each philosopher
void	initiate_simulation(t_simulation *simulation)
{
	void	*task; // to hold the function pointer for the task to be executed by the threads
	int		i;

	i = 0;
	if (simulation->nbs_philosophers == 1)
		task = single_philosopher; // task pointer to the function for a single philosopher
	else
		task = multiple_philosophers; // task pointer to the function for multiple philosophers
	simulation->start_time = get_timestamp();
	while (i < simulation->nbs_philosophers)
	{
		simulation->philosophers[i].time_last_meal = simulation->start_time;
		if (pthread_create(
				&simulation->philosophers[i].philo_thread,
				NULL,
				task,
				&simulation->philosophers[i]
			) != 0)
			printf("Thread %d failed.\n", simulation->philosophers[i].id);
		i++;
	}
	if (task == multiple_philosophers)
		monitor_death(simulation);
}

// wait for all the philosophers to finish their tasks and destroy the mutexes
// used to synchronize the threads and ensure that they finish their tasks before exiting the program
void	end_simulation(t_simulation *simulation)
{
	int	i;

	i = 0;
	while (i < simulation->nbs_philosophers)
	{
		pthread_join(simulation->philosophers[i].philo_thread, NULL);
		i++;
	}
	destroy_mutexes(simulation);
}

// get the arguments from the command line and store them in the simulation structure after checking if they are valid
static int	parse_arguments(t_simulation *sim, int ac, const char **av)
{
	sim->nbs_philosophers = ft_atoi(av[1]);
	sim->time_to_die = ft_atoi(av[2]);
	sim->time_to_eat = ft_atoi(av[3]);
	sim->time_to_sleep = ft_atoi(av[4]);
	sim->died = 0;
	sim->finish_eat = 0;
	if (ac == 6)
		sim->meals_to_eat = ft_atoi(av[5]);
	else
		sim->meals_to_eat = -1;
	return (1);
}

int	main(int argc, const char *argv[])
{
	t_simulation	simulation;

	if (!check_number_of_arguments(argc, argv))
		return (1);
	if (!check_inputs(argc, argv))
		return (1);
	if (!parse_arguments(&simulation, argc, argv))
		return (1);
	if (!init_philosophers(&simulation))
		return (1);
	if (!init_mutexes(&simulation))
	{
		free(simulation.philosophers);
		free(simulation.forks);
		return (1);
	}
	initiate_simulation(&simulation);
	end_simulation(&simulation);
	return (0);
}
