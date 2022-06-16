/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:06:38 by wcollen           #+#    #+#             */
/*   Updated: 2022/06/16 11:59:13 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*wait_threads(void *ph_param)
{
	t_sets	*set;
	int		i;
	int		status;
	
	set = ph_param;
	i = 0;
	while (i < set->ph_count)
	{
		wait(&status);
		i++;
	}
	sem_post(set->death_sem);
	return (NULL);
}



void	philo_eat(t_philo * philo)
{
	t_sets *set;

	set = philo->set;
	sem_wait(set->forks_sem);
	print(philo, "has taken a fork");
	sem_wait(set->forks_sem);
	print(philo, "has taken a fork");
	sem_wait(philo->ph_access_sem);
	philo->last_eating = get_time_now();
	sem_post(philo->ph_access_sem);
	print(philo, "is eating");
	smart_sleep(set->time_to_eat);
	sem_wait(philo->ph_access_sem);
	philo->ph_cnt_eating++;
	sem_post(philo->ph_access_sem);
	sem_post(set->forks_sem);
	sem_post(set->forks_sem);
}



void	philo_life(t_philo *philo)
{
	t_sets	*set;
	long	ph_cnt_eating;
	long	total_eating;

	set = philo->set;
	while (1)
	{
		if(are_you_already_dead(set))
			return ; //?????????????????????????
		philo_eat(philo);
		total_eating = philo->set->cnt_eatings;
		sem_wait(philo->ph_access_sem);
		ph_cnt_eating = philo->ph_cnt_eating;
		sem_post(philo->ph_access_sem);	
		if (total_eating != -1 && ph_cnt_eating >= total_eating)
		{
			sem_wait(philo->ph_access_sem);
			philo->ph_ate_flag = 1;
			sem_post(philo->ph_access_sem);
		}
		if (are_you_already_dead(philo->set))
			return ;
		print(philo, "is sleeping");
		smart_sleep(philo->set->time_to_sleep);
		print(philo, "is thinking");
	}
	return ;

}



void	start_philo_life_process(t_philo *philo)
{
	philo->last_eating = get_time_now();
	pthread_create(&(philo->set->th_live_cntrl), NULL, check_life, &philo);
	philo_life(philo);
}

void	create_processes(t_philo *philos, t_sets *set)
{
	int		i;
	pid_t	pid;

	i = -1;	
	while(++i < set->ph_count)
	{	
		philos[i].num = i + 1;
		philos[i].ph_cnt_eating = 0;
		philos[i].ph_ate_flag = 0;
		philos[i].set = set;
		philos[i].last_eating = get_time_now();
		sem_unlink("/ph_access_sem");
		philos[i].ph_access_sem = sem_open("/ph_access_sem", O_CREAT, 0644, 1);
		pid = fork();
		if (pid == 0)
		{
			start_philo_life_process(&philos[i]);
			//return (0);
			exit(0);/////?????????????
			//Когда потомок вызывает exit(), код возврата передается родителю, который ожидает его, вызывая wait()
		}
		else
		{
			philos[i].pid = pid;
			usleep(1);
		}
	}
}

int	main(int argc, char **argv)
{
	t_sets		set;
	t_philo		*philos;
	pthread_t	lives;

	if (check_args(argc, argv, &set))
		return (1);	
	fill_set(&set);
	if (init_philos(&philos, &set))
		return (error_msg("Allocation memory error!"));
	create_processes(philos, &set);
	pthread_create(&lives, NULL, wait_threads, &set);
	make_free_and_destroy(philos, &set);
	return (0);
}