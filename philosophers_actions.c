/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_actions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharajli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:16:30 by mharajli          #+#    #+#             */
/*   Updated: 2025/04/14 12:16:32 by mharajli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_philosophers.h"

// used to release the fork (to put the fork back to the table) after eating
void	release_forks(t_fork *forks)
{
	pthread_mutex_lock(&forks->fork_mutex);
	forks->philo_taken_by = 0;
	pthread_mutex_unlock(&forks->fork_mutex);
}

void	eat(t_philosopher *philo)
{
	while (1)
	{
		if (check_forks(philo, &philo->simulation->forks[philo->right_fork])) // checks if the right fork is available
			break ;
		usleep(100);
	}
	while (1)
	{
		if (check_forks(philo, &philo->simulation->forks[philo->left_fork])) // checks if the left fork is available
			break ;
		usleep(100);
	}
	// both available left and right forks then start eating
	pthread_mutex_lock(&philo->simulation->is_eating);
	action_log(philo, "is eating");
	philo->time_last_meal = get_timestamp(); // time_last_meal is the time when the philosopher started eating
	pthread_mutex_unlock(&philo->simulation->is_eating);
	time_to_pass(philo->simulation->time_to_eat, philo->simulation); // pass the time to eat
	pthread_mutex_lock(&philo->simulation->has_eaten);
	philo->eat_count++; // ++ the number of meals eaten by the philosopher (important for the simulation to end)
	pthread_mutex_unlock(&philo->simulation->has_eaten);
	release_forks(&philo->simulation->forks[philo->right_fork]); // release the right fork
	release_forks(&philo->simulation->forks[philo->left_fork]); // 	release the left fork
}

// this function is to print the action of the philosopher (philo->id) and the action (action) in the format "time id action"
void	action_log(t_philosopher *philosopher, char *action)
{
	pthread_mutex_lock((&philosopher->simulation->print));
	if (!has_philosopher_died(philosopher->simulation))
	{
		if (!has_simulation_ended(philosopher->simulation))
		{
			printf("%ld %d %s\n",
				get_timestamp() - philosopher->simulation->start_time, // from the start of the simulation to the current time
				philosopher->id,
				action);
		}
	}
	pthread_mutex_unlock(&(philosopher->simulation->print));
}

// function to put the moniter thread as dead since their is a philosopher died or the simulation has ended(the philos eat all the meals)
void	moniter_death(t_simulation *simulation)
{
	int	i;

	while (!has_simulation_ended(simulation))
	{
		i = 0;
		while (i < simulation->nbs_philosophers
			&& !has_philosopher_died(simulation))
		{
			pthread_mutex_lock(&simulation->is_eating); // this mutex is used for last_meal_time to be updated while (has_eaten for eat_count variable in philosopher struct)
			if (get_timestamp() - simulation->philosophers[i].time_last_meal
				> simulation->time_to_die)
				handle_philosopher_death(simulation, i); // this loop is to check if a philosopher has died then go handle_death of thia philo
			pthread_mutex_unlock(&simulation->is_eating);
			usleep(100);
			i++;
		}
		if (has_philosopher_died(simulation))
			break ;
		check_end_of_eating(simulation); // here to check if all the philosophers have finished eating
	}
}

// in this put the simulation->died = 1 (means philosoppher died) and print the message of the philosopher died
void	handle_philosopher_death(t_simulation *simulation, int i)
{
	pthread_mutex_lock(&simulation->moniter_die);
	simulation->died = 1;
	pthread_mutex_unlock(&simulation->moniter_die);
	pthread_mutex_lock(&simulation->print);
	printf("%ld %d %s\n",
		get_timestamp() - simulation->start_time,
		simulation->philosophers[i].id,
		"died");
	pthread_mutex_unlock(&simulation->print);
}
