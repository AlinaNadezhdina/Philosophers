/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:02:07 by wcollen           #+#    #+#             */
/*   Updated: 2022/06/22 12:46:36 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
#include  <semaphore.h>
#include  <signal.h>

struct s_sets;

typedef struct s_philo
{
	pthread_t		thread;
	struct s_sets	*set;
	pid_t			pid;
	int				num;
	long			last_eating;
	long			ph_cnt_eating;
	sem_t			*ph_access_sem;
	sem_t			*eat_cnt_sem;
}t_philo;

typedef struct s_sets
{
	int			flag_death;
	int			flag_all_ate;
	int			ph_count;
	long		start_time;
	long		time_to_die;
	long		time_to_eat;
	long 		time_to_sleep;
	long 		cnt_eatings;
	pthread_t	th_live_cntrl;
	sem_t		*forks_sem;
	// sem_t		*print_sem;
	sem_t		*death_or_ate_sem;
	// sem_t		*death_flag_sem;
	t_philo		*philos;
}t_sets;


//================ft_atoi_bonus.c================//
int		ft_atoi(const char *str);

//===============detect_errors_bonus.c============//
int		is_negative_args(int count, char **arg);
int		error_msg(char *str);

//==============parse_args_bonus.c============//
int		parse_args(char **argv, t_sets	*set);

//==============init_bonus.c================//
int 	init(char **argv, t_sets *set);
int		check_args(int argc, char **argv);

//===============food_life_monitor_bonus.c============//
void	*death_monitor(void *param);
void	*food_monitor(void *ph_param);
int		start_meal_count_thread(t_sets *set);

//=================utils_bonus.c===============//
long	get_time_now();
void	smart_sleep(unsigned long time_to_sleep);
void	print(t_philo *philo, char *str);
void	print_die(t_philo *philo);
int		are_you_already_dead(t_sets *set);


//==================free_and_destroy.c=======//
int		make_free_and_destroy(t_sets *set);
int		kill_processes(t_sets *set);
#endif