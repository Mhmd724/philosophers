/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharajli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:55:50 by mharajli          #+#    #+#             */
/*   Updated: 2025/04/14 11:55:55 by mharajli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_philosophers.h"

int	check_forks(t_philosopher *philo, t_fork *fork) // this function is to check the availability of the fork (if there is a fork available)
{
	pthread_mutex_lock(&fork->fork_mutex);
	if (!fork->philo_taken_by) // here if philo_taken_by is 0 take the id of the philo that wants to take the fork
	{
		action_log(philo, "has taken a fork.");
		fork->philo_taken_by = philo->id;
		pthread_mutex_unlock(&fork->fork_mutex);
		return (1);
	}
	else if (fork->philo_taken_by == philo->id) // if equal then the philo already taken the fork then just unlock the mutex return 1(true)
	{
		pthread_mutex_unlock(&fork->fork_mutex);
		return (1);
	}
	pthread_mutex_unlock(&fork->fork_mutex); // else unlock the mutex and return 0 (false) didn't take the fork
	return (0);
}

int	has_philosopher_died(t_simulation *simulation) // to check if there is a philosopher died (simulation->died = 1 means that there is a philosopher died)
{
	pthread_mutex_lock(&simulation->moniter_die);
	if (simulation->died)
	{
		pthread_mutex_unlock(&simulation->moniter_die);
		return (1);
	}
	pthread_mutex_unlock(&simulation->moniter_die);
	return (0);
}

int	has_simulation_ended(t_simulation *simulation) // to check if the simulation has ended (simulation->finish_eat = 1 means that the simulation has ended)
{
	pthread_mutex_lock(&simulation->moniter_end);
	if (simulation->finish_eat)
	{
		pthread_mutex_unlock(&simulation->moniter_end);
		return (1);
	}
	pthread_mutex_unlock(&simulation->moniter_end);
	return (0);
}

int	has_philosopher_finished_eating(t_philosopher *philo) // to check if the philosopher has finished eating (philo->eat_count >= simulation->meals_to_eat means that the philosopher has finished eating)
{
	pthread_mutex_lock(&philo->simulation->has_eaten);
	if (philo->eat_count >= philo->simulation->meals_to_eat)
	{
		pthread_mutex_unlock(&philo->simulation->has_eaten);
		return (1);
	}
	pthread_mutex_unlock(&philo->simulation->has_eaten);
	return (0);
}

void	check_end_of_eating(t_simulation *simulation) // to check if all philosophers have finished eating (if all philosophers have finished eating, the simulation has ended)
{
	int	i;

	i = 0;
	if (simulation->meals_to_eat == -1)
		return ;
	while (i < simulation->nbs_philosophers
		&& has_philosopher_finished_eating(&simulation->philosophers[i]))
		i++;
	if (i == simulation->nbs_philosophers)
	{
		pthread_mutex_lock(&simulation->moniter_end);
		simulation->finish_eat = 1;
		pthread_mutex_unlock(&simulation->moniter_end);
		pthread_mutex_lock(&simulation->print);
		printf("number of meals eaten: %d\n", simulation->meals_to_eat);
		pthread_mutex_unlock(&simulation->print);
	}
}
