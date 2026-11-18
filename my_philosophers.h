/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_philosophers.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharajli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:58:43 by mharajli          #+#    #+#             */
/*   Updated: 2025/04/14 12:58:44 by mharajli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_PHILOSOPHERS_H
# define MY_PHILOSOPHERS_H

# include <stdio.h> // needed for printf and perror
# include <stdlib.h> // needed for malloc and free
# include <pthread.h> // needed for pthreads and mutexes
# include <unistd.h> // needed for usleep
# include <sys/time.h> // needed for gettimeofday
# include <limits.h> // needed for INT_MAX and INT_MIN

typedef struct s_fork
{
	pthread_mutex_t	fork_mutex; // mutex to protect the fork from concurrent access
	int				philo_taken_by; // id of the philosopher who is currently using the fork
}	t_fork;

typedef struct s_philosopher
{
	struct s_simulation	*simulation; // pointer to the simulation structure
	pthread_t			philo_thread; // thread for the philosopher
	int					id; // philosopher's id
	int					eat_count; // number of meals eaten by the philosopher (important for the optional argument that is entered (meals_to_eat))
	int					left_fork; // id of the left fork
	int					right_fork; // id of the right fork
	long int			time_last_meal; // timestamp of the last meal eaten by the philosopher
}	t_philosopher;

typedef struct s_simulation
{
	t_philosopher	*philosophers; // array of philosophers
	t_fork			*forks; // array of forks
	pthread_mutex_t	print; // mutex for printing actions to the console (thread-safe) thread by thread prints
	pthread_mutex_t	is_eating; // mutex to protect the eating state of the philosophers (last meal time variable)
	pthread_mutex_t	has_eaten; // mutex to protect the eating count of the philosophers (eat_count variable)
	pthread_mutex_t	monitor_die; // mutex to protect the death state of the philosophers (died variable) (monitor knows if a philosopher has died or not by this variable)
	pthread_mutex_t	monitor_end; // mutex to protect the end of the simulation (finish_eat variable) (monitor knows if a philosopher has finished eating or not by this variable)
	long int		start_time; // timestamp of the start of the simulation
	int				nbs_philosophers; // number of philosophers
	int				time_to_die; // time in milliseconds before a philosopher dies (if he doesn't eat)
	int				time_to_eat; // time in milliseconds to eat a meal
	int				time_to_sleep; // time in milliseconds to sleep after eating
	int				meals_to_eat; // number of meals to eat (optional argument)
	int				died; // flag to indicate if a philosopher has died (1 if dead, 0 if alive)
	int				finish_eat; // flag to indicate if the simulation has ended (1 if finished, 0 if not)
}	t_simulation;

void		destroy_mutexes(t_simulation *simulation);
void		monitor_death(t_simulation *simulation);
void		handle_philosopher_death(t_simulation *simulation, int i);
void		check_end_of_eating(t_simulation *simulation);
void		*single_philosopher(void *philosopher);
void		*multiple_philosophers(void *philosopher);
void		eat(t_philosopher *philo);
void		action_log(t_philosopher *philosopher, char *action);
void		release_forks(t_fork *forks);
void		time_to_pass(long int time_in_ms, t_simulation *simulation);
long int	get_timestamp(void);
int			init_mutexes(t_simulation *simulation);
int			check_number_of_arguments(int ac, const char **av);
int			check_inputs(int ac, const char **av);
int			ft_atoi(const char *av);
int			init_philosophers(t_simulation *simulation);
int			check_forks(t_philosopher *philo, t_fork *fork);
int			has_philosopher_died(t_simulation *simulation);
int			has_simulation_ended(t_simulation *simulation);
int			has_philosopher_finished_eating(t_philosopher *philo);

#endif
