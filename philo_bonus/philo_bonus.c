/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:06:38 by wcollen           #+#    #+#             */
/*   Updated: 2022/06/22 14:19:44 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_eat(t_philo * philo)
{
	t_sets *set;
	int current_index;
	int passed_index;

	set = philo->set;

	current_index = philo->num-1;
	printf("- %d entered the queue\n", philo->num);
	sem_wait(set->queue_sems[current_index]); // queue lock

	sem_wait(set->forks_sem);
	print(philo, "has taken a fork");
	if (set->ph_count == 1)
	{
		sem_post(set->forks_sem);
		return ;
	}
	sem_wait(set->forks_sem);
	print(philo, "has taken a fork");

	long time = get_time_now();
	sem_wait(philo->ph_access_sem);
	philo->last_eating = time;
	sem_post(philo->ph_access_sem);

	print(philo, "is eating");
	smart_sleep(set->time_to_eat);

	sem_wait(philo->ph_access_sem);
	philo->ph_cnt_eating++;
	sem_post(philo->ph_access_sem);
	
	sem_post(set->forks_sem);
	sem_post(set->forks_sem);

	passed_index = (current_index + 1) % set->ph_count;
	sem_post(set->queue_sems[passed_index]); // pass queue to the next philosopher
	printf("- %d passed the queue to %d\n", philo->num, passed_index + 1);
}

void	philo_life(t_philo *philo)
{
	t_sets	*set;
	long	ph_cnt_eating;
	long	total_eating;

	set = philo->set;
	while (1)
	{
		print(philo, "before checking if dead");
		if(are_you_already_dead(set))
			return ;
		philo_eat(philo);
		total_eating = philo->set->cnt_eatings;
		// sem_wait(philo->ph_access_sem);
		ph_cnt_eating = philo->ph_cnt_eating;
		// sem_post(philo->ph_access_sem);	
		if (total_eating != -1 && ph_cnt_eating >= total_eating)
		{			
			sem_post(philo->eat_cnt_sem);
		}
		if (are_you_already_dead(philo->set))
			return ;
		print(philo, "is sleeping");
		smart_sleep(philo->set->time_to_sleep);
		print(philo, "is thinking");
	}
	return ;
}

int	start_philo_life_process(t_philo *philo)
{
	philo->last_eating = get_time_now();
	if (pthread_create(&(philo->set->th_live_cntrl), NULL, death_monitor, philo) != 0)
		return (1);
	philo_life(philo);
	//pthread_join(philo->set->th_live_cntrl, NULL);
	pthread_detach(philo->set->th_live_cntrl);
	return (0);
}

int	create_processes(t_sets *set)
{
	int		i;
	t_philo *philos;

	philos = set->philos;
	i = -1;	
	while(++i < set->ph_count)
	{	
		philos[i].pid = fork();		
		if (philos[i].pid == -1)
			return (error_msg("fork creation error"));
		if (philos[i].pid == 0)
		{
			start_philo_life_process(&philos[i]);			
			exit(0);
		}
		//usleep(100);
	}

	start_meal_count_thread(set);
	
	// //В случае успешного выполнения wait() возвращает ID процесса завершившегося потомка
	// int status;
	// while (waitpid(-1, &status, 0) > 0)
	// {
	// 	if (WEXITSTATUS(status) == 1)
	// 		return (kill_processes(set));
	// }
	
	return (0);
}

int	main(int argc, char **argv)
{
	t_sets		set;

	if (check_args(argc, argv))
		return (1);
	if (init(argv, &set) || create_processes(&set))
		return (error_msg("error: fatal!\n") && make_free_and_destroy(&set));

	sem_wait(set.death_or_ate_sem);// sem_post в потоке еды и в потоке смерти
	
	kill_processes(&set);
	make_free_and_destroy(&set);
	return (0);
}