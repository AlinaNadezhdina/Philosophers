/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:02:07 by wcollen           #+#    #+#             */
/*   Updated: 2022/06/25 23:38:02 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <semaphore.h>
# include <signal.h>

struct	s_sets;

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
	long		time_to_sleep;
	long		cnt_eatings;
	pthread_t	th_live_cntrl;
	pthread_t	shutdown_wait;
	sem_t		*forks_sem;
	sem_t		**queue_sems;
	sem_t		*shutdown_signal_sem;
	sem_t		*launch_sem;
	sem_t		*print_sem;
	sem_t		*death_or_ate_sem;
	sem_t		*death_flag_sem;
	t_philo		*philos;
}t_sets;

//================ft_atoi_bonus.c================//
int		ft_atoi(const char *str);

//================from_libft.c==================//
char	*ft_itoa(int n);
char	*ft_strjoin(char const *s1, char const *s2);

//===============detect_errors_bonus.c============//
int		is_negative_args(int count, char **arg);
int		error_msg(char *str);

//==============parse_args_bonus.c============//
int		parse_args(char **argv, t_sets	*set);

//==============init_bonus.c================//
int		init(char **argv, t_sets *set);
int		check_args(int argc, char **argv);
sem_t	*open_semaphore(char *name, int val);

//===============food_death_monitor_bonus.c============//
void	*death_monitor(void *param);
void	*food_monitor(void *param);
int		start_meal_count_thread(t_sets *set);
void	*wait_for_shutdown(void *param);

//=================utils_bonus.c===============//
long	get_time_now(void);
void	print(t_philo *philo, char *str);
void	print_die(t_philo *philo);
int		are_you_already_dead(t_sets *set);
void	set_flag_death_value(t_sets *set);

//=================utils_bonus2.c===============//
char	*make_semaphore_name(int num);
int		single_philo_must_die(t_philo *philo);
int		not_count_food_if_ph_died(t_philo *philo, int already_post_flag);

//==================free_and_destroy.c=======//
int		make_free_and_destroy(t_sets *set);
int		kill_processes(t_sets *set);

#endif