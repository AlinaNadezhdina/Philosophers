/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:06:38 by wcollen           #+#    #+#             */
/*   Updated: 2022/06/24 18:13:41 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_eat(t_philo * philo)
{
	t_sets *set;
	int current_index;
	int passed_index;

	set = philo->set;

	current_index = philo->num - 1;
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
	usleep(set->time_to_eat * 1000);

	sem_wait(philo->ph_access_sem);
	philo->ph_cnt_eating++;
	sem_post(philo->ph_access_sem);
	
	sem_post(set->forks_sem);
	sem_post(set->forks_sem);

	passed_index = (current_index + 1) % set->ph_count;
	sem_post(set->queue_sems[passed_index]); // pass queue to the next philosopher
}

void	philo_life(t_philo *philo)
{
	t_sets	*set;
	long	ph_cnt_eating;
	long	total_eating;
	int		already_post_flag;

	already_post_flag = 0;

	set = philo->set;
	while (1)
	{
		if(are_you_already_dead(set))
		{
			//флаг нужен в случае, когда фил умер, не доев нужное количество, 
			//а семафор фила eat_cnt_sem в потоке food_monitor так и продолжает ждать когда фил сделает sem_post(philo->eat_cnt_sem)
			if (already_post_flag == 0)
				sem_post(philo->eat_cnt_sem);
			return ;
		}
			
		philo_eat(philo);
		total_eating = philo->set->cnt_eatings;
		sem_wait(philo->ph_access_sem);
		ph_cnt_eating = philo->ph_cnt_eating;
		sem_post(philo->ph_access_sem);	
		if (total_eating != -1 && ph_cnt_eating >= total_eating  && already_post_flag == 0)
		{			
			sem_post(philo->eat_cnt_sem);
			already_post_flag = 1;
		}
		if (are_you_already_dead(philo->set))
		{
			if (already_post_flag == 0)
				sem_post(philo->eat_cnt_sem);
			return ;
		}
		print(philo, "is sleeping");
		usleep(philo->set->time_to_sleep * 1000);
		print(philo, "is thinking");
	}
	return ;
}



int	start_philo_life_process(t_philo *philo)
{
	philo->last_eating = get_time_now();
	if (pthread_create(&(philo->set->th_live_cntrl), NULL, death_monitor, philo) != 0)
		return (1);
	if (pthread_create(&(philo->set->shutdown_wait), NULL, wait_for_shutdown, philo) != 0)
		return (1);

	pthread_detach(philo->set->th_live_cntrl);
	pthread_detach(philo->set->shutdown_wait);

	philo_life(philo);
	return (0);
}

int	create_processes(t_sets *set)
{
	sem_t *launch_sem;
	int		i;
	t_philo *philos;

	philos = set->philos;
	i = -1;	
	launch_sem = sem_open("/launch", O_CREAT, 0644, 0);
	while(++i < set->ph_count)
	{	
		philos[i].pid = fork();		
		if (philos[i].pid == -1)
			return (error_msg("fork creation error"));
		if (philos[i].pid == 0)
		{
			sem_wait(launch_sem);
			start_philo_life_process(&philos[i]);			
			exit(0);
		}
	}
	start_meal_count_thread(set);
	for (int i = 0; i < set->ph_count; i++)
	{
		sem_post(launch_sem);
	}
	sem_close(launch_sem);
	sem_unlink("/launch");
	
	return (0);
}

int	main(int argc, char **argv)
{
	t_sets	set;
	int		status;

	if (check_args(argc, argv))
		return (1);
	if (init(argv, &set) || create_processes(&set))
		return (error_msg("error: fatal!\n") && make_free_and_destroy(&set));
	sem_wait(set.death_or_ate_sem);// sem_post в потоке еды и в потоке смерти
	for(int i = 0; i < set.ph_count; i++) {
		sem_post(set.shutdown_signal_sem);//открываем семафор, который ждет поток каждого фила,
									  //чтобы выставить флаг смерти в 1 и завершить потоки жизни и смерти
	}
	//В случае успешного выполнения wait() возвращает ID процесса завершившегося потомка
	while (waitpid(-1, &status, 0) > 0)
	{
		 if (WEXITSTATUS(status))//WEXITSTATUS возвращает код завершения потомка 
		 								//возвращает истинное значение, если потомок нормально завершился
		 	return (kill_processes(&set));
	}
	make_free_and_destroy(&set);
	return (0);
}